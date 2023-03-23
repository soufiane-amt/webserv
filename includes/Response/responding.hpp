/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:21:12 by samajat           #+#    #+#             */
/*   Updated: 2023/03/23 17:32:11 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONDING_HPP
#define RESPONDING_HPP

#include "utils.hpp"
#include "exception.hpp"



//Status-Line

class responsePreparation
{
    private:
        typedef std::string     response_t;
        typedef std::string     statusCode_t;
    
        http_message_t          _request;
        response_t              _response;
        statusCode_t            _statusCode;

    public:
        responsePreparation(const http_message_t& request, const  statusCode_t& );
        
        response_t         get_response() const;
        

    private:
        void               prepare_statusLine();
        void               prepare_other_headers();
        void               prepare_body();
        std::string        get_file_content(const std::string& uri);
};

#endif