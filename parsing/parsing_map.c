#include "parsing.h"


static int	is_in_set(char c, const char *set)
{
	int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i2;
	size_t	i1;
	size_t	r;
	size_t	len;
	char	*strtrim;

	if (s1 == NULL)
		return (NULL);
	if (set == NULL)
		return (ft_strdup(s1));
	i1 = 0;
	i2 = ft_strlen(s1);
	r = 0;
	while (s1[i1] != '\0' && is_in_set(s1[i1], set))
		i1++;
	while (i2 > i1 && is_in_set(s1[i2 - 1], set))
		i2--;
	len = i2 - i1;
	strtrim = (char *)malloc((len + 1) * sizeof(char));
	if (strtrim == NULL)
		return (NULL);
	while (i1 < i2)
		strtrim[r++] = s1[i1++];
	strtrim[r] = '\0';
	return (strtrim);
}


long long start_of_map(char **file)
{
    int i = 0;
    int j = 0;
    int found_config = 0;
    int config_need = 6;

    while (file[i])
    {
        j = 0;
        while (file[i][j] == ' ' || (file[i][j] >= 9 && file[i][j] <= 13))
            j++;
        if ((ft_strncmp(file[i] + j, "NO", 2) == 0 || ft_strncmp(file[i] + j, "SO", 2) == 0
            || ft_strncmp(file[i] + j, "EA", 2) == 0 || ft_strncmp(file[i] + j, "WE", 2) == 0
            || ft_strncmp(file[i] + j, "F", 1) == 0 || ft_strncmp(file[i] + j, "C", 1) == 0))
                found_config += 1;
        else if (found_config == config_need && 
                 file[i][j] != '\0' && file[i][j] != '\n')
                return i;
        i++;
    }
    return -1;
}

void extract_and_pars_the_map(t_utils *util, char **file)
{
    long long map_start = start_of_map(file);
    char **map;
    int map_line = 0;
    int total_lines = 0;
    int i;
    int j;

    if (map_start == -1)
    {
        write(2, "Error\nNo map found\n", 20);
        exit(2);
    }
    
    i = map_start;
    while (file[i])
    {
        total_lines++;
        i++;
    }
    
    map = malloc(sizeof(char *) * (total_lines + 1));
    if (!map)
    {
        write(2, "Memory allocation failed\n", 25);
        exit(2);
    }
    i = map_start;
    while (file[i] && map_line < total_lines)
    {
        map[map_line] = strdup(file[i]);
        if (!map[map_line])
        {
            write(2, "Memory allocation failed\n", 25);
            j = 0;
            while (j < map_line)
            {
                free(map[j]);
                j++;
            }
            free(map);
            exit(2);
        }
        map_line++;
        i++;
    }
    map[map_line] = NULL;
    util->map = map;
    pars_the_map(util);
}

void check_for_valid_character_in_map(char str)
{
    if (str != '0' && str != '1'
        && str != 'N' && str != 'S'
        && str != 'E' && str != 'W' && str != ' ' && str != '\n')
    {
        write(2, "Error\nNon valid character in the map\n", 38);
        exit(2);
    }
}

void check_first_line(char **str)
{
    int i = 0;
    int j = 0;

    while (str && str[i][j])
    {
        if (str[i][j] == '0' || str[i][j] == 'N' || str[i][j] == 'S' || str[i][j] == 'E' || str[i][j] == 'W')
        {
            printf("44--------------------\n");
            write(2, "Error\nthe Map is open\n", 23);
            exit(2);
        }
        if (str[i][j] == ' ' && str[i+1][j] == '0')
        {
            printf("999--------------------\n");
            write(2, "Error\nthe Map is open\n", 23);
            exit(2);
        }
        j++;
    }
}
int lent(char **str)
{
    int i = 0;
    while(str && str[i])
        i++;
    return (i);
}

void check_the_last_line(char **str)
{
    int i = lent(str) - 1;
    int j = 0;

    while (str && str[i] && str[i][j])
    {
        if (str[i][j] == '0' || str[i][j] == 'N' || str[i][j] == 'S' || str[i][j] == 'E' || str[i][j] == 'W')
        {
            printf("785--------------------\n");
            write(2, "Error\nthe Map is open\n", 23);
            exit(2);
        }
        if (str[i][j] == ' ' && str[i-1][j] == '0')
        {
            printf("147--------------------\n");
            write(2, "Error\nthe Map is open\n", 23);
            exit(2);
        }
        j++;
    }

}

void pars_the_map_helper(t_utils *util)
{
    int i = 1;
    int j = 0;
    int len;
    int last_char;

    while(util->map[i])
    {
        j = 0;
        if (strcmp(util->map[i], "\n") == 0)
        {
            i++;
            continue;
        }
        len = strlen(util->map[i]);
        last_char = len - 1;
        while (util->map[i][j] == ' ' || (util->map[i][j] >= 9 && util->map[i][j] <= 13))
           j++;
        if (last_char >= 0 && (util->map[i][last_char] == '\n'))
            last_char--;
        while ((util->map[i][last_char] == ' ' || (util->map[i][last_char] >= 9 && util->map[i][last_char] <= 13)))
           last_char--;
        if (util->map[i][last_char] == '\n' || util->map[i][last_char] == ' ')
            util->map[i][last_char] = '\0';
        if (util->map[i][j] != '1' || (last_char >= 0 && util->map[i][last_char] != '1'))
        {
            printf("-47-------------------\n");
            write(2, "Error\nthe Map is open\n", 23);
            exit(2);
        }
        i++;
    }
    check_first_line(util->map);
    check_the_last_line(util->map);
}
void pars_the_map(t_utils *util)
{
    unsigned long i = 0;
    unsigned long j = 0;
    int player = 0;

    while (util->map[i])
    {

        j = 0;
        while (util->map[i][j] == ' ' || (util->map[i][j] >= 9 && util->map[i][j] <= 13))
            j++;
        while (util->map[i][j])
        {
            check_for_valid_character_in_map(util->map[i][j]);
            if (util->map[i][j] == 'N' || util->map[i][j] == 'S' || util->map[i][j] == 'E' || util->map[i][j] == 'W')
                player++;
            if (util->map[i][strlen(util->map[i]) - 1] == '\n')
                util->map[i][strlen(util->map[i]) - 1] = '\0';
            if (util->map[i][j] == ' ')
            {
                 if (util->map && util->map[i] && util->map[i][j] && i > 0 && j > 0 && util->map[i+1] != NULL && util->map[i][j+1] != '\0' &&
                    strlen(util->map[i-1]) > j && strlen(util->map[i+1]) > j &&
                 ((util->map[i][j+1] != '1' && util->map[i][j+1] != ' ') || (util->map[i][j-1] != '1' && util->map[i][j-1] != ' ')
                    || (util->map[i-1][j] != '1' && util->map[i-1][j] != ' ') || (util->map[i+1][j] != '1' && util->map[i+1][j] != ' ')))
                    {
                        printf("[%s]\n", util->map[i]);
                        printf("14--------------------\n");
                        write(2, "Error\nthe Map is open\n", 23);
                        exit(2);
                    }
            }
            else if (util->map[i][j] == '0')
            {
                if (util->map && util->map[i] && util->map[i][j] && i > 0 && j > 0 && util->map[i+1] != NULL && util->map[i][j+1] != '\0' &&
                    strlen(util->map[i-1]) > j && strlen(util->map[i+1]) > j &&
                 ((util->map[i][j+1] == ' ') || (util->map[i][j-1] == ' ')
                    || (util->map[i-1][j] == ' ') || (util->map[i+1][j] == ' ')))
                    {
                        printf("--7--4----------------\n");
                        write(2, "Error\nthe Map is open\n", 23);
                        exit(2);
                    }
            }
            j++;
        }
        i++;
    }
    if (player != 1)
        {
            write(2, "Error\nThere more the one player\n", 33);
            player = 0;
            exit(2);
        }
    pars_the_map_helper(util);
}