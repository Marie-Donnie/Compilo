#include "parser_GPL.h"

bool parse_GPL(Ptr *p){
  if (p->op_type == CONC){
    return parse_GPL(p->op.conc->left) && parse_GPL(p->op.conc->right);
  }
  else if (p->op_type == UNION){
    return parse_GPL(p->op.uni->left) || parse_GPL(p->op.uni->right);
  }
  else if (p->op_type == STAR){
    while (parse_GPL(p->op.star->stare)) {}
    return true;
  }
  else if (p->op_type == UN){
    if (parse_GPL(p->op.un->une)) {}
    return true;
  }
  else if (p->op_type == ATOM){
    if (p->op.atom->a_type == TERMINAL){

      printf("atom: %s token: %s\n", p->op.atom->code, scan_token()->type);

      if (!strcmp(p->op.atom->code, scan_token()->type)){
	if (p->op.atom->action != 0){
	  GPL_action(p->op.atom->action);
	}
	scan_GPL();
	return true;
      }
      else {
	return false;
      }
    }
    else if (p->op.atom->a_type == NON_TERMINAL){
      if (parse_GPL(get_rule_by_head(p->op.atom->code)->body)){
	if (p->op.atom->action != 0){
	  GPL_action(p->op.atom->action);
	}
	return true;
      }
      else {
	return false;
      }
    }
  }
  return false;
}

void GPL_action(int action){

}
