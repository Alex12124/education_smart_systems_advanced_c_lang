#include <stdio.h>
#include <string.h>

int min(int a, int b)
{
    return a < b ? a : b;
}

void zFunction(char *s, int z[]) {
    int n = strlen(s);
    for (int i = 1, l = 0, r = 0; i < n; ++i) {
        if (i <= r) {
            z[i] = min(r - i + 1, z[i - l]);
        }
        while (i + z[i] < n && s[z[i]] == s[i + z[i]]) {
            ++z[i];
        }
        if (i + z[i] - 1 > r) {
            l = i, r = i + z[i] - 1;
        }
    }
}

int get_first_position_suffix(char *str)
{
    int len = strlen(str);
    for (int i = len - 1; i >= 0; i--)
    {
        if (str[i] == '_')
        {
            return i + 1;
        }
    }
    return 0;
}

int get_last_position_prefix(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] == '_')
        {
            return i - 1;
        }
    }
    return len - 1;
}

int max_substr_sz(char* prefix, int prefix_sz, char* suffix, int suffix_sz)
{
    char res[2048] = {0}; 
    int z[2048] = {0};
    memcpy(res, prefix, prefix_sz);
    memcpy(res + prefix_sz, suffix, suffix_sz);
    zFunction(res, z);
    int res_len = strlen(res);

    int maximum = 0;
    for (int i = prefix_sz; i < res_len; i++)
    {
        if (z[i] > maximum && z[i] + i == res_len)
        {
            maximum = z[i];
        }
        
    }
    return maximum;
}



int main() {
    char s1[1024];
    char s2[1024];
    
    scanf("%s", s1);
    scanf("%s", s2);
    int len_s1 = strlen(s1);
    int len_s2 = strlen(s2);

    if (len_s1 == 0 || len_s2 == 0)
    {
        printf("%d %d\n", 0, 0);
        return 0;
    }

    int prefix_pos = get_last_position_prefix(s1);
    int suffix_pos = get_first_position_suffix(s2);
    int sz = max_substr_sz(s1, prefix_pos + 1, s2 + suffix_pos, len_s2 - suffix_pos);
    
    printf("%d ", sz);

    prefix_pos = get_last_position_prefix(s2);
    suffix_pos = get_first_position_suffix(s1);
    sz = max_substr_sz(s2, prefix_pos + 1, s1 + suffix_pos, len_s1 - suffix_pos);
    
    printf("%d\n", sz);

    return 0;
}
