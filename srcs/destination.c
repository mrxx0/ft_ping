#include "../includes/ft_ping.h"

t_payload *create_payload(void)
{
    t_payload *payload = NULL;

    payload = malloc(sizeof(t_payload));
    payload->address = NULL;
    payload->opt = 0;
    payload->id_opt = 0;
    payload->found_address = 0;
    return (payload);
}

_Bool    parse_address(char *str, t_payload *payload)
{
    size_t i = 0;
    size_t dots = 0;
    size_t members = 0;

    while (str[i])
    {
        if (str[i] != '.' && ft_isdigit(str[i]) == EXIT_FAILURE)
        {
            printf("Failure for is digit\n");
            return (EXIT_FAILURE);
        }
        else if (str[i] != '.')
            members++;
        if (str[i] == '.')
        {
            if (members > 3)
            {
                printf("Failure for members at %zu \n", members);
                return (EXIT_FAILURE);
            }
            dots++;
            members = 0;
        }
        i++;
    }
    if (i == ft_strlen(str))
    {
        if (dots == 3)
        {
            payload->address = ft_strdup(str);
            payload->found_address = 1;
            printf("Seems ok\n");
            return(EXIT_SUCCESS);
        }
    }
    
    printf("Failure for size\n");
    return (EXIT_FAILURE);     
}

_Bool    get_destination(int argc, char **argv, t_payload *payload)
{
    int i = 1;

    while (i < argc)
    {
        if (i != payload->id_opt && payload->found_address == 0)
        {
            if (parse_address(argv[i], payload) == EXIT_FAILURE)
                return (EXIT_FAILURE);
            else
                i++;
        }
        else
            i++;
    }
    return (EXIT_SUCCESS);
}