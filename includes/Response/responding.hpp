/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   responding.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samajat <samajat@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/22 20:21:12 by samajat           #+#    #+#             */
/*   Updated: 2023/06/23 23:20:33 by samajat          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RESPONDING_HPP
#define RESPONDING_HPP

#include "utils.hpp"
#include "exception.hpp"
#include "cgiProgram.hpp"


//Status-Line /***********you should use different classes for this************/
class responsePreparation
{
    private:
        typedef std::vector<char>     response_t;
    
        http_message_t          _request;
        StatusCode              _statusCode;
        response_t              _response;
        bool                    _dir_listing_on;

        std::string             _allowed_methods;

        location_t              server_locations;
        int                     id;
    public:
        responsePreparation(const http_message_t& request, int targeted_serv, const  StatusCode& = StatusCode("200 OK"));
        
        response_t&         get_response() ;
        

    private:
        void             prepare_statusLine();

        void             prepare_server_name();
        void             prepare_date();
        void             prepare_location();
        void             prepare_last_modified();
        void             prepare_eTag();
    
        void             prepare_content_length(response_t::iterator& ite);
        void             prepare_content_type(response_t::iterator& ite);
        void             prepare_meta_body_data();

        void             add_CRLF();

        void             prepare_allow();

        void             prepare_connection();
        void             prepare_body();

        void             exceute_get();
        void             exceute_post();
        void             exceute_delete();


        void             prepare_error_response();      
        std::string      get_mime_type(const std::string& filename);

        response_t::iterator    _find_in_response(const std::string& str);
        void                    _init(int targeted_serv);
        void                    change_status_line(const char *status_code);

        bool             file__delet_is_allowed(const std::string& file_path);

        void             set_env_variables_for_cgi();
        void             execute_cgi();
};

#endif