/* Generated by ./xlat/gen.sh from ./xlat/epollflags.in; do not edit. */

static const struct xlat epollflags[] = {
#if defined(EPOLL_CLOEXEC) || (defined(HAVE_DECL_EPOLL_CLOEXEC) && HAVE_DECL_EPOLL_CLOEXEC)
 XLAT(EPOLL_CLOEXEC),
#endif
#if defined(EPOLL_NONBLOCK) || (defined(HAVE_DECL_EPOLL_NONBLOCK) && HAVE_DECL_EPOLL_NONBLOCK)
 XLAT(EPOLL_NONBLOCK),
#endif
 XLAT_END
};