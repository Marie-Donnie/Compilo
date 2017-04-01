#include "parser_GPL.h"

/* bool parse(Ptr *p){ */
/*   if (p->op_type == CONC){ */
/*     return parse(p->op.conc->left) && parse(p->op.conc->right); */
/*   } */
/*   else if (p->op_type == UNION){ */
/*     return parse(p->op.uni->left) || parse(p->op.uni->right); */
/*   } */
/*   else if (p->op_type == STAR){ */
/*     while (parse(p->op.star->stare)) {} */
/*     return true; */
/*   } */
/*   else if (p->op_type == UN){ */
/*     if (parse(p->op.un->une)) {} */
/*     return true; */
/*   } */
/*   else if (p->op_type == ATOM){ */
/*     if (p->op.atom->a_type == TERMINAL){ */
/*       if (!strcmp(p->op.atom->code, scan_token()->type)){ */
/* 	if (p->op.atom->action != 0){ */
/* 	  g0_action(p->op.atom->action); */
/* 	} */
/* 	scan(); */
/* 	return true; */
/*       } */
/*       else { */
/* 	return false; */
/*       } */
/*     } */
/*     else if (p->op.atom->a_type == NON_TERMINAL){ */
/*       if (parse(get_rule_by_head(p->op.atom->code)->body)){ */
/* 	if (p->op.atom->action != 0){ */
/* 	  g0_action(p->op.atom->action); */
/* 	} */
/* 	return true; */
/*       } */
/*       else { */
/* 	return false; */
/*       } */
/*     } */
/*   } */
/*   return false; */
/* } */
