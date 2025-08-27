#include "parsing.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	if (i == n)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}
void free_split(char **split)
{
    int i = 0;

    while (split[i])
        {
            free(split[i]);
            i++;
        }
    free(split);
}
void extract_and_pars_the_texture(t_utils *util, char **file)
{
    int i = 0;
    // int j = 0;
    char **texture;
    int fd;

    int done_no = 0;
    int done_so = 0;
    int done_we = 0;
    int done_ea = 0;

    while (file[i])
    {
        if(strnstr(file[i], "./", strlen(file[i])) != NULL) 
        {
            if(ft_strncmp(file[i], "NO", 2) == 0
            || ft_strncmp(file[i], "SO", 2) == 0
            || ft_strncmp(file[i], "EA", 2) == 0
            || ft_strncmp(file[i], "WE", 2) == 0)
            {
                texture = ft_split(file[i], ' ');
                if (texture[1][strlen(texture[1]) - 1] == '\n')
                    texture[1][strlen(texture[1]) - 1] = '\0';
                if(strcmp(texture[0], "NO") == 0 && done_no == 0)
                {
                     fd = open(texture[1], O_RDONLY);
                    print_error(fd);
                    util->no_fd = fd;
                    done_no = 1;
                    free_split(texture);
                }
                else if (strcmp(texture[0], "SO") == 0 && done_so == 0)
                {
                     fd = open(texture[1], O_RDONLY);
                    print_error(fd);
                    util->so_fd = fd;
                    done_so = 1;
                    free_split(texture);
                }
                else if (strcmp(texture[0], "EA") == 0 && done_ea == 0)
                {
                     fd = open(texture[1], O_RDONLY);
                    print_error(fd);
                    util->ea_fd = fd;
                    done_ea = 1;
                    free_split(texture);
                }
                else if (strcmp(texture[0], "WE") == 0 && done_we == 0)
                {
                     fd = open(texture[1], O_RDONLY);
                        print_error(fd);
                    util->we_fd = fd;
                    done_we = 1;
                    free_split(texture);
                }
               else if ((strcmp(texture[0], "NO") == 0 && done_no == 1)
                    || (strcmp(texture[0], "SO") == 0 && done_so == 1)
                    || (strcmp(texture[0], "EA") == 0 && done_ea == 1)
                    || (strcmp(texture[0], "WE") == 0 && done_we == 1))
                    {
                    write(2, "Duplicate identifier\n", 22);
                    free_split(texture);
                    exit(2);
                    }
                else
                {
                    write(2, "not valide identifier\n", 23);
                    free_split(texture);
                    exit(2);
                }
            }
        }
        i++;
    }
}
