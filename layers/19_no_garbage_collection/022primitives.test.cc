void test_fn_works() {
  cell* result = run("(fn(x) x)");
  // {sig: (x), body: (x)}
  CHECK_EQ(car(get(result, sym_sig)), new_sym("x"));
  CHECK_EQ(cdr(get(result, sym_sig)), nil);
  CHECK_EQ(car(get(result, sym_body)), new_sym("x"));
  CHECK_EQ(cdr(get(result, sym_body)), nil);
}



void test_if_sees_args_in_then_and_else() {
  run("(<- f (fn(x) (if 34 x)))");
  CLEAR_TRACE;
  run("(f 35)");
  CHECK_TRACE_TOP("eval", "=> 35\n");
}

void test_not_works() {
  run("(not 35)");
  CHECK_TRACE_TOP("eval", "compiled fn\n=> nil\n");
}

void test_not_works2() {
  run("(not nil)");
  CHECK_TRACE_TOP("eval", "compiled fn\n=> 1\n");
}

void test_cons_works() {
  run("(cons 1 2)");
  CHECK_TRACE_TOP("eval", "compiled fn\n=> (1 ... 2)\n");
}

void test_assign_to_non_sym_warns() {
  run("(<- 3 nil)");
  CHECK_EQ(Raise_count, 1);   Raise_count=0;
}

void test_assign_lexical_var() {
  run("((fn (x) (<- x 34) x))");
  CHECK_TRACE_TOP("eval", "=> 34\n");
}

void test_assign_overrides_dynamic_vars() {
  run("(<- x 3)");
  run("(<- x 5)");
  CLEAR_TRACE;
  run("x");
  CHECK_TRACE_TOP("eval", "sym\n=> 5\n");
}

void test_assign_overrides_within_lexical_scope() {
  run("(<- x 3)");
  run("((fn () (<- x 5)))");
  CLEAR_TRACE;
  run("x");
  CHECK_TRACE_TOP("eval", "sym\n=> 5\n");
}

void test_assign_never_overrides_lexical_vars_in_caller_scope() {
  run("((fn (x) (<- y x)) 34)");
  CLEAR_TRACE;
  run("y");
  CHECK_TRACE_CONTENTS("eval", "sym\n=> 34\n");
}

void test_assign_overrides_lexical_var() {
  run("((fn (x) (<- x 35) (<- x 36) x) 34)");
  CHECK_TRACE_TOP("eval", "=> 36\n");
}

void test_equal_handles_nil() {
  run("(= nil nil)");
  CHECK_TRACE_DOESNT_CONTAIN("eval", 1, "=> nil\n");
}

void test_equal_handles_floats() {
  run("(= (/ 3.0 2) 1.5)");
  CHECK_TRACE_DOESNT_CONTAIN("eval", 1, "=> nil\n");
}

void test_equal_handles_float_vs_nil() {
  run("(= nil 1.5)");
  CHECK_EQ(Raise_count, 0);
  CHECK_TRACE_TOP("eval", "compiled fn\n=> nil\n");
}
