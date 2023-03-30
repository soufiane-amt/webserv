/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:21:12 by samajat           #+#    #+#             */
/*   Updated: 2023/03/30 20:48:01 by samajat          ###   ########.fr       */
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
    
        http_message_t          _request;
        const  StatusCode&      _statusCode;
        response_t              _response;

    public:
        responsePreparation(const http_message_t& request, const  StatusCode& = StatusCode("200 OK"));
        
        response_t         get_response() const;
        

    private:
        void               prepare_statusLine();
        void               prepare_other_headers();
        void               prepare_rest();
        void               prepare_content_length();
        void               prepare_content_type();
        void               prepare_last_modified();
        void               prepare_allow();
        void               exceute_get();
        void               exceute_post();
        void               exceute_delete();

        void               sendError();        
};

#endif