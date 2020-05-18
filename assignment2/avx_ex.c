#include <stdio.h>
#include <stddef.h>
#if defined(_MSC_VER) || defined(__MINGW32__)
#  include <malloc.h>
#else
#  include <stdlib.h>
#endif  /* defined(_MSC_VER) || defined(__MINGW32__) */
 
#ifndef __cplusplus
#  if defined(_MSC_VER)
#    define inline      __inline
#    define __inline__  __inline
#  elif !defined(__GNUC__) && !defined(__STDC_VERSION__) || __STDC_VERSION__ < 199901L
#    define inline
#    define __inline
#  endif
#endif
 
 
/*!
 * @brief アラインメントされたメモリを動的確保する関数
 * @param [in] size       確保するメモリサイズ (単位はbyte)
 * @param [in] alignment  アラインメント (2のべき乗を指定すること)
 * @return  アラインメントし，動的確保されたメモリ領域へのポインタ
 */
static inline void*
alignedMalloc(size_t size, size_t alignment)
{
#if defined(_MSC_VER) || defined(__MINGW32__)
  return _aligned_malloc(size, alignment);
#else
  void* p;
  return posix_memalign((void**) &p, alignment, size) == 0 ? p : NULL;
#endif  /* _MSC_VER */
}
 
 
/*!
 * @brief アラインメントされたメモリを解放する関数
 * @param [in] ptr  解放対象のメモリの先頭番地を指すポインタ
 */
static inline void
alignedFree(void* ptr)
{
#if defined(_MSC_VER) || defined(__MINGW32__)
  _aligned_free(ptr);
#else
  free(ptr);
#endif  /* _MSC_VER */
}
 
 
/* 以下，利用コード */
 
 
int
main(void)
{
  static const int ALIGN = 32;
  unsigned char* array = (unsigned char*) alignedMalloc(10 * sizeof(unsigned char), ALIGN);
  if (array == NULL) {
    fprintf(stderr, "Failed to allocate memory\n");
    return 1;
  }
 
  if (((ptrdiff_t) array) % ALIGN == 0) {
    printf("Dynamic allocated memory is %d byte aligned.\n", ALIGN);
  } else {
    printf("Dynamic allocated memory is not %d byte aligned.\n", ALIGN);
  }
  alignedFree(array);
 
  return 0;
}