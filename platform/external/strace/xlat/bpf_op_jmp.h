/* Generated by ./xlat/gen.sh from ./xlat/bpf_op_jmp.in; do not edit. */

static const struct xlat bpf_op_jmp[] = {
#if defined(BPF_JA) || (defined(HAVE_DECL_BPF_JA) && HAVE_DECL_BPF_JA)
 XLAT(BPF_JA),
#endif
#if defined(BPF_JEQ) || (defined(HAVE_DECL_BPF_JEQ) && HAVE_DECL_BPF_JEQ)
 XLAT(BPF_JEQ),
#endif
#if defined(BPF_JGT) || (defined(HAVE_DECL_BPF_JGT) && HAVE_DECL_BPF_JGT)
 XLAT(BPF_JGT),
#endif
#if defined(BPF_JGE) || (defined(HAVE_DECL_BPF_JGE) && HAVE_DECL_BPF_JGE)
 XLAT(BPF_JGE),
#endif
#if defined(BPF_JSET) || (defined(HAVE_DECL_BPF_JSET) && HAVE_DECL_BPF_JSET)
 XLAT(BPF_JSET),
#endif
#if defined(BPF_JNE) || (defined(HAVE_DECL_BPF_JNE) && HAVE_DECL_BPF_JNE)
 XLAT(BPF_JNE),
#endif
#if defined(BPF_JSGT) || (defined(HAVE_DECL_BPF_JSGT) && HAVE_DECL_BPF_JSGT)
 XLAT(BPF_JSGT),
#endif
#if defined(BPF_JSGE) || (defined(HAVE_DECL_BPF_JSGE) && HAVE_DECL_BPF_JSGE)
 XLAT(BPF_JSGE),
#endif
#if defined(BPF_CALL) || (defined(HAVE_DECL_BPF_CALL) && HAVE_DECL_BPF_CALL)
 XLAT(BPF_CALL),
#endif
#if defined(BPF_EXIT) || (defined(HAVE_DECL_BPF_EXIT) && HAVE_DECL_BPF_EXIT)
 XLAT(BPF_EXIT),
#endif
 XLAT_END
};