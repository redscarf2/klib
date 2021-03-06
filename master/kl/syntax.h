#ifndef _kl_syntax_h_
#define _kl_syntax_h_

#include "token.h"
#include "symbols.h"
#include "node.h"


// syntax parser module
class syntax_parser
{
public:
    syntax_parser() ;

    // init syntax parser
    bool init(inter_env* env);

    // parser tokens and return the sytax tree
    sytax_node* parser_tokens(const token_list_type& thelist) ;

protected:
    void init_pos(const token_list_type& thelist);
    sytax_node* alloc_node(node_type type = type_statement);
    const token* get_next_token();
    const token* get_cur_token();

private:
    sytax_node* parser_name_def(const token* tk);
    sytax_node* parser_var_def(const token* tk);
    sytax_node* parser_function_def(const token* tk);
    sytax_node* parser_array_def(const token* tk);
    bool is_match(const token* tk, token_type type);

private:
    const token_list_type* token_list_;
    token_list_type::const_iterator itr_;

    inter_env* inter_env_;
};



#endif // _kl_syntax_h_