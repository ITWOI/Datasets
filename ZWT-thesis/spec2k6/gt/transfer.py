import json
import argparse
import sys
import os


def parse_line(line):
    """
    解析单行文本，提取 Call Site 和 Target。
    预期格式: Call_Site: 0x... -> Target: 0x...
    """
    try:
        if "->" not in line:
            return None, None

        parts = line.split('->')

        # 解析左边: "Call_Site: 0x417fc9 "
        call_site_part = parts[0].strip()
        # 解析右边: " Target: 0x400b00"
        target_part = parts[1].strip()

        # 提取具体的地址
        # 使用 split(':')[-1] 取冒号后的最后一部分，兼容前面可能有也可能没有空格的情况
        call_site_addr = call_site_part.split(':')[-1].strip()
        target_addr = target_part.split(':')[-1].strip()

        return call_site_addr, target_addr
    except Exception as e:
        print(f"[Warning] 解析出错行: '{line.strip()}' - {e}")
        return None, None


def process_file(input_path, output_path):
    result = {}
    count = 0

    # 1. & 2. 读取并解析数据 (流式处理)
    try:
        with open(input_path, 'r', encoding='utf-8') as f:
            # 直接遍历文件对象 f，而不是使用 f.readlines()
            for line in f:
                print(line) # 建议：如果是大文件，打印每一行会严重拖慢速度，建议注释掉
                line = line.strip()
                if not line:
                    continue

                # 注意：这里假设 parse_line 函数在外部已定义
                site, target = parse_line(line)

                if site and target:
                    if site not in result:
                        result[site] = []

                    # 逻辑：防止同一个 Call Site 添加重复的 Target
                    # 注意：如果 result[site] 列表很大，这里的 `in` 判断会变慢
                    # 针对超大数据集，建议将 value 存为 set，最后转为 list
                    if target not in result[site]:
                        result[site].append(target)

                    count += 1

    except FileNotFoundError:
        print(f"[Error] 找不到输入文件: {input_path}")
        sys.exit(1)
    except Exception as e:
        print(f"[Error] 读取或解析文件时发生错误: {e}")
        sys.exit(1)

    print(f"[Info] 已处理 {count} 行数据，提取出 {len(result)} 个唯一的 Call Sites。")

    # 3. 写入 JSON 输出文件
    try:
        with open(output_path, 'w', encoding='utf-8') as f:
            json.dump(result, f, indent=4)
        print(f"[Success] 转换完成！JSON 已保存至: {output_path}")
    except IOError as e:
        print(f"[Error] 写入文件失败: {e}")
        sys.exit(1)


if __name__ == "__main__":
    # 配置命令行参数解析
    parser = argparse.ArgumentParser(description="将 Call Site 文本日志转换为 JSON 格式。")

    # 定义参数
    parser.add_argument('-i', '--input', required=True, help="输入文件的路径 (txt)")
    parser.add_argument('-o', '--output', required=True, help="输出文件的路径 (json)")

    args = parser.parse_args()

    # 执行主逻辑
    process_file(args.input, args.output)