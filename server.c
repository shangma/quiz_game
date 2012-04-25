/*
 Structure of Client Handler
 * int link
 * client number
 * buffer
 * timeout
 * answers[]
 * 
 * read_buffer()
 * write_buffer()
 * 
 * get_answers()
 * ask_question()
 * 
 * get_all_answers() 
 */

/*
 Server Behavior
 * ask for number of clients and then collect
 * create new clients
 * place new clients in thread
 * store client links in clients[]
 * 
 * read in questions
 * send questions to clients
 * get answers from clients
 * send answers to clients 
 * 
 * calculate winner 
 
 */