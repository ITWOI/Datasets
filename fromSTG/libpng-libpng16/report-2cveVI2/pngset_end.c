#include "header_func.h"
extern void png_set_text (png_const_structrp png_ptr, png_inforp info_ptr, png_const_textp text_ptr, int num_text){
    int ret;
    ret = png_set_text_2(png_ptr, info_ptr, text_ptr, num_text);
}
extern int png_set_text_2 (png_const_structrp png_ptr, png_inforp info_ptr, png_const_textp text_ptr, int num_text){
    int i;
    if (png_ptr == ((void *)0) || info_ptr == ((void *)0) || num_text <= 0 || text_ptr == ((void *)0))
        return 0;
    if (num_text > info_ptr->max_text - info_ptr->num_text) {
        int old_num_text = info_ptr->num_text;
        int max_text;
        png_textp new_text = ((void *)0);
        max_text = old_num_text;
        if (num_text <= 2147483647 - max_text) {
            max_text += num_text;
            if (max_text < 2147483647 - 8)
                max_text = (max_text + 8) & ~7;
            else
                max_text = 2147483647;
            new_text = (png_realloc_array(png_ptr, info_ptr->text, old_num_text, max_text - old_num_text, sizeof *new_text));
        }
        if (new_text == ((void *)0)) {
            ;
            return 1;
        }
        ;
        info_ptr->text = new_text;
        info_ptr->free_me |= 16384U;
        info_ptr->max_text = max_text;
    }
    for (i = 0; i < num_text; i++) {
        size_t text_length, key_len;
        size_t lang_len, lang_key_len;
        png_textp textp = &(info_ptr->text[info_ptr->num_text]);
        if (text_ptr[i].key == ((void *)0))
            continue;
        if (text_ptr[i].compression < -1 || text_ptr[i].compression >= 3) {
            ;
            continue;
        }
        key_len = strlen(text_ptr[i].key);
        if (text_ptr[i].compression <= 0) {
            lang_len = 0;
            lang_key_len = 0;
        } else {
            if (text_ptr[i].lang != ((void *)0)) {
                lang_len = strlen(text_ptr[i].lang);
            } else
                lang_len = 0;
            if (text_ptr[i].lang_key != ((void *)0)) {
                lang_key_len = strlen(text_ptr[i].lang_key);
            } else
                lang_key_len = 0;
        }
        if (text_ptr[i].text == ((void *)0) || text_ptr[i].text[0] == '\x00') {
            text_length = 0;
            if (text_ptr[i].compression > 0)
                textp->compression = 1;
            else
                textp->compression = -1;
        } else {
            text_length = strlen(text_ptr[i].text);
            textp->compression = text_ptr[i].compression;
        }
        textp->key = (png_malloc_base(png_ptr, key_len + text_length + lang_len + lang_key_len + 4));
        if (textp->key == ((void *)0)) {
            ;
            return 1;
        }
        ;
        *(textp->key + key_len) = '\x00';
        if (text_ptr[i].compression > 0) {
            textp->lang = textp->key + key_len + 1;
            *(textp->lang + lang_len) = '\x00';
            textp->lang_key = textp->lang + lang_len + 1;
            memcpy(textp->lang_key, text_ptr[i].lang_key, lang_key_len);
            *(textp->lang_key + lang_key_len) = '\x00';
            textp->text = textp->lang_key + lang_key_len + 1;
        } else {
            textp->lang = ((void *)0);
            textp->lang_key = ((void *)0);
            textp->text = textp->key + key_len + 1;
        }
        ;
        *(textp->text + text_length) = '\x00';
        if (textp->compression > 0) {
            textp->text_length = 0;
            textp->itxt_length = text_length;
        } else {
            textp->text_length = text_length;
            textp->itxt_length = 0;
        }
        info_ptr->num_text++;
    }
    return 0;
}
