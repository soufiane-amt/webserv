/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:21:12 by samajat           #+#    #+#             */
/*   Updated: 2023/04/08 21:14:54 by samajat          ###   ########.fr       */
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
        typedef std::stringstream     response_t;
    
        http_message_t          _request;
        const  StatusCode&      _statusCode;
        response_t              _response;

    public:
        responsePreparation(const http_message_t& request, const  StatusCode& = StatusCode("200 OK"));
        
        response_t&         get_response() ;
        

    private:
        void               prepare_rest();
        void               prepare_other_headers();
        
        
        void               prepare_statusLine();
        
        void               prepare_server_name();
        void               prepare_date();
        void               prepare_location();
        void               prepare_content_length();
        
        
        void               add_CRLF();
        
        void               prepare_allow();
        void               prepare_body();
        
        void               exceute_get();
        // void               exceute_post();
        // void               exceute_delete();

        void               prepare_error_response();        
};

#endif