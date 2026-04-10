#include "header_func.h"
static inline int is_bit_set_in_table (uint32_t *table, int bitindex){
    uint32_t word = table[bitindex >> 5];
    return (word >> (bitindex & 31)) & 1;
}
static inline int is_jump (struct instr *i){
    return is_bit_set_in_table(_PyOpcode_Jump, i->i_opcode);
}
static int stack_effect (int opcode, int oparg, int jump){
    switch (opcode) {
      case 9:
      case 144:
        return 0;
      case 1:
        return -1;
      case 2:
      case 3:
      case 6:
        return 0;
      case 4:
        return 1;
      case 5:
        return 2;
      case 10:
      case 11:
      case 12:
      case 15:
        return 0;
      case 146:
      case 145:
        return -1;
      case 147:
        return -2;
      case 19:
      case 20:
      case 16:
      case 22:
      case 23:
      case 24:
      case 25:
      case 26:
      case 27:
        return -1;
      case 28:
      case 29:
        return -1;
      case 55:
      case 56:
      case 57:
      case 17:
      case 59:
        return -1;
      case 60:
        return -3;
      case 61:
        return -2;
      case 62:
      case 63:
      case 64:
      case 65:
      case 66:
        return -1;
      case 67:
        return -1;
      case 68:
        return 0;
      case 70:
        return -1;
      case 71:
        return 1;
      case 75:
      case 76:
      case 77:
      case 78:
      case 79:
        return -1;
      case 143:
        return jump ? 6 : 1;
      case 83:
        return -1;
      case 84:
        return -1;
      case 85:
        return 0;
      case 86:
        return 0;
      case 72:
        return -1;
      case 87:
        return 0;
      case 89:
        return -3;
      case 90:
        return -1;
      case 91:
        return 0;
      case 92:
        return oparg - 1;
      case 94:
        return (oparg & 255) + (oparg >> 8);
      case 93:
        return jump > 0 ? -1 : 1;
      case 95:
        return -2;
      case 96:
        return -1;
      case 97:
        return -1;
      case 98:
        return 0;
      case 100:
        return 1;
      case 101:
        return 1;
      case 102:
      case 103:
      case 104:
      case 157:
        return 1 - oparg;
      case 105:
        return 1 - 2 * oparg;
      case 156:
        return -oparg;
      case 106:
        return 0;
      case 107:
      case 117:
      case 118:
        return -1;
      case 121:
        return -2;
      case 108:
        return -1;
      case 109:
        return 1;
      case 110:
      case 113:
        return 0;
      case 112:
      case 111:
        return jump ? 0 : -1;
      case 114:
      case 115:
        return -1;
      case 116:
        return 1;
      case 122:
        return jump ? 6 : 0;
      case 119:
        return -3;
      case 49:
        return 1;
      case 124:
        return 1;
      case 125:
        return -1;
      case 126:
        return 0;
      case 130:
        return -oparg;
      case 131:
        return -oparg;
      case 161:
        return -oparg - 1;
      case 141:
        return -oparg - 1;
      case 142:
        return -1 - ((oparg & 1) != 0);
      case 132:
        return -1 - ((oparg & 1) != 0) - ((oparg & 2) != 0) - ((oparg & 4) != 0) - ((oparg & 8) != 0);
      case 133:
        if (oparg == 3) {
            return -2;
        } else
            return -1;
      case 135:
        return 1;
      case 136:
      case 148:
        return 1;
      case 137:
        return -1;
      case 138:
        return 0;
      case 73:
        return 0;
      case 154:
        return jump ? -1 + 6 : 0;
      case 52:
        return 1;
      case 50:
        return 0;
      case 51:
        return 1;
      case 69:
        return 0;
      case 54:
        return -7;
      case 155:
        return (oparg & 4) == 4 ? -1 : 0;
      case 160:
        return 1;
      case 74:
        return 1;
      case 82:
        return 0;
      case 129:
        return -1;
      case 162:
      case 163:
      case 164:
      case 165:
        return -1;
      case 34:
        return 0;
      case 152:
        return -1;
      case 30:
      case 31:
      case 32:
        return 1;
      case 33:
        return 2;
      case 99:
        return 0;
      default:
        return 2147483647;
    }
    return 2147483647;
}
static inline void stackdepth_push (basicblock ***sp, basicblock *b, int depth){
    ;
    if (b->b_startdepth < depth && b->b_startdepth < 100) {
        ;
        b->b_startdepth = depth;
        *(*sp)++ = b;
    }
}
static int stackdepth (struct compiler *c){
    basicblock *b, *entryblock = ((void *)0);
    basicblock **stack, **sp;
    int nblocks = 0, maxdepth = 0;
    for (b = c->u->u_blocks; b != ((void *)0); b = b->b_list) {
        b->b_startdepth = (-2147483647 - 1);
        entryblock = b;
        nblocks++;
    }
    ;
    stack = (basicblock **)PyObject_Malloc(sizeof(basicblock *) * nblocks);
    if (!stack) {
        ;
        return -1;
    }
    sp = stack;
    if (c->u->u_ste->ste_generator || c->u->u_ste->ste_coroutine) {
        stackdepth_push(&sp, entryblock, 1);
    } else {
        stackdepth_push(&sp, entryblock, 0);
    }
    while (sp != stack)
        {
            b = *--sp;
            int depth = b->b_startdepth;
            basicblock *next = b->b_next;
            for (int i = 0; i < b->b_iused; i++) {
                struct instr *instr = &b->b_instr[i];
                int effect = stack_effect(instr->i_opcode, instr->i_oparg, 0);
                if (effect == 2147483647) {
                    ;
                    return -1;
                }
                int new_depth = depth + effect;
                if (new_depth > maxdepth) {
                    maxdepth = new_depth;
                }
                ;
                if (is_jump(instr)) {
                    effect = stack_effect(instr->i_opcode, instr->i_oparg, 1);
                    int target_depth = depth + effect;
                    stackdepth_push(&sp, instr->i_target, target_depth);
                }
                depth = new_depth;
                if (instr->i_opcode == 113 || instr->i_opcode == 110 || instr->i_opcode == 83 || instr->i_opcode == 130 || instr->i_opcode == 119) {
                    next = ((void *)0);
                    break;
                }
            }
            if (next != ((void *)0)) {
                ;
                stackdepth_push(&sp, next, depth);
            }
        }
    ;
    return maxdepth;
}
