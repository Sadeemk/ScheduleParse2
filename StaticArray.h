// Programmer: Sadeem Khan
// Programmer's ID: 1549921

#ifndef StaticArray_h
#define StaticArray_h

template <typename V, int CAP>
class StaticArray
{
  V values[CAP];
  V dummy;

  public:
  StaticArray();
  int capacity() const {return CAP;}
  V operator[](int) const;
  V& operator[](int);
};

template <typename V, int CAP>
StaticArray<V, CAP>::StaticArray()
{
  for (int index = 0; index < CAP; index++) 
  	values[index] = V();
}

template <typename V, int CAP>
V StaticArray<V, CAP>::operator[](int index) const
{
 if (index < 0) return dummy;
 if (index >= CAP) return dummy;
 return values[index];
}

template <typename V, int CAP>
V& StaticArray<V, CAP>::operator[](int index)
{
 if (index < 0) return dummy;
 if (index >= CAP) return dummy;
 return values[index];
}
#endif