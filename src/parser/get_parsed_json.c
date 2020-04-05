/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_parsed_json.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cschoen <cschoen@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/05 05:45:33 by cschoen           #+#    #+#             */
/*   Updated: 2020/04/05 05:46:22 by cschoen          ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

json_object	*get_parsed_json(char *file_name)
{
	int			fd;
	int			text_size;
	char		*parse_text;
	json_object	*parsed_json;

	if ((fd = open(file_name, O_RDONLY)) < 0)
		ft_error("Can't open the file for parsing");
	if (!(parse_text = ft_strnew(PARSE_TEXT_SIZE)))
		ft_error("Can't allocate memory for parsing the file");
	if ((text_size = read(fd, parse_text, PARSE_TEXT_SIZE)) < 0)
		ft_error("Can't read the file for parsing");
	if (text_size == 0 || text_size >= PARSE_TEXT_SIZE)
		ft_error("Max size/Empty parsing file");
	close(fd);
	parsed_json = json_tokener_parse(parse_text);
	ft_strdel(&parse_text);
	return (parsed_json);
}
