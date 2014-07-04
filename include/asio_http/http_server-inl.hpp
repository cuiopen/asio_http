#if !defined(ASIO_HTTP_HTTP_SERVER_INCLUDED_H_)
#error "Invalid include order"
#endif

template <typename RequestHandler>
http_server<RequestHandler>::http_server(boost::asio::io_service & io_svc,
		boost::asio::ip::tcp::endpoint endpoint_)
	: io_svc_(io_svc)
	, acceptor_(io_svc_, endpoint_)
{
	start_accept();
}

template <typename RequestHandler>
void http_server<RequestHandler>::start_accept()
{
    connection_type::pointer new_connection =
		connection_type::create(io_svc_);
	acceptor_.async_accept(new_connection->socket(),
		boost::bind(&http_server<RequestHandler>::handle_accept, this, new_connection,
		boost::asio::placeholders::error));
}

template <typename RequestHandler>
void http_server<RequestHandler>::handle_accept(connection_type::pointer new_connection,
	const boost::system::error_code& error)
{
    if (!error)
    {
		new_connection->start();
		start_accept();
    }
}