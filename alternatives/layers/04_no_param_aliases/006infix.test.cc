void test_infix_passes_atoms() {
  IndentSensitiveStream in("abc");
  AstNode n = nextAstNode(in);
  check(isAtom(n));
  checkEq(transformInfix(n), n.atom);
}

void test_infix_passes_ellipses() {
  IndentSensitiveStream in("...");
  AstNode n = nextAstNode(in);
  check(isAtom(n));
  checkEq(transformInfix(n), n.atom);
}

void test_infix_passes_atoms2() {
  IndentSensitiveStream in("-3.2");
  AstNode n = nextAstNode(in);
  check(isAtom(n));
  checkEq(transformInfix(n), n.atom);
}

void test_infix_passes_strings() {
  IndentSensitiveStream in("\"a b+c\"");
  AstNode n = nextAstNode(in);
  check(isAtom(n));
  checkEq(transformInfix(n), n.atom);
}

void test_infix_passes_floats() {
  IndentSensitiveStream in("2e-2");
  AstNode n = nextAstNode(in);
  checkEq(transformInfix(n), n.atom);
}

void test_infix_passes_dollar_vars() {
  IndentSensitiveStream in("$a");
  AstNode n = nextAstNode(in);
  check(isAtom(n));
  checkEq(transformInfix(n), n.atom);
}

void test_infix_handles_dollar_op() {
  IndentSensitiveStream in("$+");
  checkEq(transformInfix(nextAstNode(in)), "$+");
}

void test_infix_handles_op_without_args() {
  IndentSensitiveStream in("(+)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isAtom(n));
  checkEq(n.atom, "+");
}

void test_infix_handles_op_without_args2() {
  IndentSensitiveStream in("(= (+) 3)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "="); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "3"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_dollar_op_without_args() {
  IndentSensitiveStream in("($+)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isAtom(n));
  checkEq(n.atom, "$+");
}

void test_infix_handles_quoting() {
  IndentSensitiveStream in("',a");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "'"); ++p;
  checkEq(*p, ","); ++p;
  checkEq(*p, "a"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_quoting2() {
  IndentSensitiveStream in("',a+b");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "'"); ++p;
  checkEq(*p, ","); ++p;
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_quoting3() {
  IndentSensitiveStream in("',(a + b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "'"); ++p;
  checkEq(*p, ","); ++p;
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_quoting4() {
  IndentSensitiveStream in("',(+)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "'"); ++p;
  checkEq(*p, ","); ++p;
  checkEq(*p, "+"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_simple_lists() {
  IndentSensitiveStream in("(a + b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_passes_wrapped_op() {
  IndentSensitiveStream in("(a (+) b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_passes_wrapped_op2() {
  IndentSensitiveStream in("(a (+) b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_infix_ops_in_prefix() {
  IndentSensitiveStream in("(+ a b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_passes_ellipses_in_infix() {
  IndentSensitiveStream in("(a ... b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "..."); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_passes_op_with_ellipses() {
  IndentSensitiveStream in("(+ ... b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "..."); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_infix_ops_in_unary_prefix() {
  IndentSensitiveStream in("(+ a)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_infix_ops_in_nested_lists() {
  IndentSensitiveStream in("((a + b))");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  checkEq(n.elems.size(), 3);
  AstNode n2 = *++n.elems.begin();
  check(isList(n2));
  list<AstNode>::iterator p = n2.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n2.elems.end());
}

void test_infix_handles_infix_ops_in_nested_lists2() {
  IndentSensitiveStream in("(do (a + b))");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "do"); ++p;
  AstNode n2 = *p; ++p;
    check(isList(n2));
    list<AstNode>::iterator p2 = n2.elems.begin();
    checkEq(*p2, "("); ++p2;
    checkEq(*p2, "+"); ++p2;
    checkEq(*p2, "a"); ++p2;
    checkEq(*p2, "b"); ++p2;
    checkEq(*p2, ")"); ++p2;
    check(p2 == n2.elems.end());
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_infix_ops_in_nested_lists3() {
  IndentSensitiveStream in("(a = (a + 1))");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "="); ++p;
  checkEq(*p, "a"); ++p;
  AstNode n2 = *p; ++p;
    check(isList(n2));
    list<AstNode>::iterator p2 = n2.elems.begin();
    checkEq(*p2, "("); ++p2;
    checkEq(*p2, "+"); ++p2;
    checkEq(*p2, "a"); ++p2;
    checkEq(*p2, "1"); ++p2;
    checkEq(*p2, ")"); ++p2;
    check(p2 == n2.elems.end());
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_left_associates() {
  IndentSensitiveStream in("(a + b + c)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  AstNode n2 = *p; ++p;
    check(isList(n2));
    list<AstNode>::iterator p2 = n2.elems.begin();
    checkEq(*p2, "("); ++p2;
    checkEq(*p2, "+"); ++p2;
    checkEq(*p2, "a"); ++p2;
    checkEq(*p2, "b"); ++p2;
    checkEq(*p2, ")"); ++p2;
    check(p2 == n2.elems.end());
  checkEq(*p, "c"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_op() {
  IndentSensitiveStream in("(a + b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_always_has_higher_precedence_than_call() {
  IndentSensitiveStream in("(f a + b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "f"); ++p;
  AstNode n2 = *p; ++p;
    check(isList(n2));
    list<AstNode>::iterator p2 = n2.elems.begin();
    checkEq(*p2, "("); ++p2;
    checkEq(*p2, "+"); ++p2;
    checkEq(*p2, "a"); ++p2;
    checkEq(*p2, "b"); ++p2;
    checkEq(*p2, ")"); ++p2;
    check(p2 == n2.elems.end());
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_always_has_lower_precedence_than_prefix() {
  IndentSensitiveStream in("-a+b");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  AstNode n2 = *p; ++p;
    check(isList(n2));
    list<AstNode>::iterator p2 = n2.elems.begin();
    checkEq(*p2, "("); ++p2;
    checkEq(*p2, "-"); ++p2;
    checkEq(*p2, "a"); ++p2;
    checkEq(*p2, ")"); ++p2;
    check(p2 == n2.elems.end());
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_multiple_infix_ops() {
  IndentSensitiveStream in("(f a + b c + d)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "f"); ++p;
  AstNode n2 = *p; ++p;
    check(isList(n2));
    list<AstNode>::iterator p2 = n2.elems.begin();
    checkEq(*p2, "("); ++p2;
    checkEq(*p2, "+"); ++p2;
    checkEq(*p2, "a"); ++p2;
    checkEq(*p2, "b"); ++p2;
    checkEq(*p2, ")"); ++p2;
    check(p2 == n2.elems.end());
  n2 = *p; ++p;
    check(isList(n2));
    p2 = n2.elems.begin();
    checkEq(*p2, "("); ++p2;
    checkEq(*p2, "+"); ++p2;
    checkEq(*p2, "c"); ++p2;
    checkEq(*p2, "d"); ++p2;
    checkEq(*p2, ")"); ++p2;
    check(p2 == n2.elems.end());
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_op_without_spaces() {
  IndentSensitiveStream in("a+b");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_op_without_spaces2() {
  IndentSensitiveStream in("$a+b");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "$a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_op_with_float() {
  IndentSensitiveStream in("a+1.0");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "1.0"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_op_with_float2() {
  IndentSensitiveStream in("3.0+1.0");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "3.0"); ++p;
  checkEq(*p, "1.0"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_op_with_float3() {
  IndentSensitiveStream in("a3.b");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "."); ++p;
  checkEq(*p, "a3"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_gives_ops_without_spaces_precedence() {
  IndentSensitiveStream in("(n * n-1)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "*"); ++p;
  checkEq(*p, "n"); ++p;
  AstNode n2 = *p; ++p;
    check(isList(n2));
    list<AstNode>::iterator p2 = n2.elems.begin();
    checkEq(*p2, "("); ++p2;
    checkEq(*p2, "-"); ++p2;
    checkEq(*p2, "n"); ++p2;
    checkEq(*p2, "1"); ++p2;
    checkEq(*p2, ")"); ++p2;
    check(p2 == n2.elems.end());
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_complement_as_usual() {
  IndentSensitiveStream in("~a.b");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "("); ++p;
  checkEq(*p, "."); ++p;
  AstNode n2 = *p; ++p;
    check(isList(n2));
    list<AstNode>::iterator p2 = n2.elems.begin();
    checkEq(*p2, "("); ++p2;
    checkEq(*p2, "~"); ++p2;
    checkEq(*p2, "a"); ++p2;
    checkEq(*p2, ")"); ++p2;
    check(p2 == n2.elems.end());
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_backquote() {
  IndentSensitiveStream in("`(a + b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "`"); ++p;
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_splice() {
  IndentSensitiveStream in("@a+b");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, "@"); ++p;
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}

void test_infix_handles_unquote_splice() {
  IndentSensitiveStream in(",@a+b");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, ",@"); ++p;
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}
void test_infix_handles_unquote_splice2() {
  IndentSensitiveStream in(",@(a + b)");
  AstNode n = transformInfix(nextAstNode(in));
  check(isList(n));
  list<AstNode>::iterator p = n.elems.begin();
  checkEq(*p, ",@"); ++p;
  checkEq(*p, "("); ++p;
  checkEq(*p, "+"); ++p;
  checkEq(*p, "a"); ++p;
  checkEq(*p, "b"); ++p;
  checkEq(*p, ")"); ++p;
  check(p == n.elems.end());
}
