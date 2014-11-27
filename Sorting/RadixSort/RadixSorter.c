# include <jni.h>
# include "RadixSorter.h"

JNIEXPORT void JNICALL Java_RadixSorter_sort (JNIEnv *env, jclass jclazz, jintArray jintArr) {
	
  void radixsort(int arr[], int n);
  jsize len;
  jint *intArr;
  
  len = (*env)->GetArrayLength(env, jintArr);
  intArr = (*env)->GetPrimitiveArrayCritical(env, jintArr, 0);

	radixsort(intArr, len);
	
  (*env)->ReleasePrimitiveArrayCritical(env, jintArr, intArr, 0);
}
