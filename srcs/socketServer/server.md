server1
{
    port;
    servername;
}

for server1=> create socketfd => bind => listen => :
        in poll:
            => if it's connection:
                => accept => newfd
            => if it's send/recv event:
                => send/recv 1024 bytes on newfd

            => in recv : read and append
            //recv() can return 0. This can mean only one thing: the //remote side has closed the connection on you!
            => in send : send and check content length maybe ?? 