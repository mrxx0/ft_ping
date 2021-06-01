#include "../includes/ft_ping.h"

_Bool print_help(void)
{
    printf("Usage: ft_ping [-hv] <destination adress>\n");
    return (EXIT_SUCCESS);
}

// _Bool check_for_option(char **argv, int8_t id_opt)
// {
//     size_t i = 0;

//     while (argv[id_opt][i] != '\0')
//     {
//         if (argv[id_opt][i] == 'v')
//         {
//             printf("v option parsed\n");
//             return (EXIT_SUCCESS);
//         }
//         else if (argv[id_opt][i] == 'h')
//             return (EXIT_FAILURE);
//         else
//             i++;
//     }
//     return (EXIT_FAILURE);
// }
void parse_opt(char *str, t_payload *payload)
{
    size_t i = 1;

    while (str[i])
    {
        if (str[i] == 'h' || str[i] == 'v')
            payload->opt |= str[i] == 'h' ? HELP : VERBOSE;
        else if (str[i] != 'h' && str[i] != 'v')
            payload->opt |= BAD_OPT;
        i++;
    }
    if (payload->opt == 0)
        payload->opt |= NO_OPT;
}

void find_opt(int argc, char **argv, t_payload *payload)
{
    int i = 0;
    int j = 0;
    payload->opt = 0;

    while (i < argc)
    {
        while (argv[i][j] != '\0')
        {
            if (argv[i][j] == '-' && payload->opt == 0)
                parse_opt(argv[i], payload);
            // if (argv[i][j] == '-' && argv[i][j + 1] == 'h')
            // {
            //     payload->opt |= HELP;
            //     if (argv[i][j + 2] == 'v')
            //         payload->opt |= VERBOSE;
            // }
            // else if (argv[i][j] == '-' && argv[i][j + 1] == 'v')
            // {
            //     payload->opt |= VERBOSE;
            //     if (argv[i][j + 2] == 'h')
            //         payload->opt |= HELP;
            // }
            // else if (argv[i][j] == '-' && (argv[i][j + 1] != 'v' && argv[i][j + 1] != 'h'))
            //     payload->opt |= BAD_OPT;
            j++;
        }
        j = 0;
        i++;
    }
    if (payload->opt == 0)
        payload->opt = NO_OPT;
}

_Bool parsing_arguments(int argc, char **argv)
{
    t_payload *payload = NULL;
    if (argc > 3)
        return (EXIT_FAILURE); 
    else if (argc >= 1)
    {
        payload = create_payload();
        if (payload == MALLOC_FAILED)
            return (EXIT_FAILURE);
        find_opt(argc, argv, payload);
        
        if ((payload->opt & HELP) == 1)
            printf("HELP\n");
        if ((payload->opt & VERBOSE) == 2)
            printf("VERBOSE\n");
        if ((payload->opt & BAD_OPT) == 4)
            printf("BAD_OPT\n");
        if ((payload->opt & NO_OPT) == 5)
            printf("NO_OPT\n");
            
        if ((payload->opt & BAD_OPT) == 4)
        {
             free(payload);
            return (EXIT_FAILURE);
        }
            // if (check_for_option(argv) == EXIT_FAILURE)
            //     return (EXIT_FAILURE);
        // if (get_destination(argc, argv, id_opt, payload) == EXIT_FAILURE)
        //     return (EXIT_FAILURE);
        // printf("address = [%s]\n", payload->address);
    }
    // if (payload->address != NULL)
    //     free(payload->address);
    free(payload);
    return (EXIT_SUCCESS);
}
