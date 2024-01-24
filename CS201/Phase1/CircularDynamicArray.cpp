#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <climits>
#include <cstring>
#include <stdlib.h>
#include <time.h>
#include <algorithm>

using namespace std;

template <typename T>


class CircularDynamicArray {
public:
    int size;
    int cap;
    int start;
    int end;
    T* arr;
    T err;
    bool reversed;

    CircularDynamicArray() {
        cap = 2;
        size = 0;
        start = 0;
        end = 0;
        arr = new T[cap];
        reversed = false;
    }

    CircularDynamicArray(int s) {
        cap = s;
        size = s;
        start = 0;
        end = s - 1;
        arr = new T[cap];
        reversed = false;
    }

    //copy constructor
    CircularDynamicArray(const CircularDynamicArray& obj){
        arr = new T[obj.cap];
        size = obj.size;
        cap = obj.cap;
        start = obj.start;
        end = obj.end;
        reversed = obj.reversed;
        copy(obj.arr, obj.arr+cap, arr);
    }

    CircularDynamicArray& operator =(CircularDynamicArray obj){
        swap(arr, obj.arr);
        swap(cap, obj.cap);
        swap(size, obj.size);
        swap(start, obj.start);
        swap(end, obj.end);
        swap(reversed, obj.reversed);
        return *this;
    }

    ~CircularDynamicArray() {
        delete[]arr;
    }

    T& operator[](int i) {
        if(!reversed){
            if (i < 0 || i >= size) {
                cout << "Error. Out of bounds." << endl;

                return err;
            }

            int index = start + i;
            if (index >= cap) {
                index -= cap;
            }
            return arr[index];
        }
        else{
            if(i < 0 || i >= size){
                cout << "Error. Out of bounds." << endl;

                return err;
            }

            int index = start - i;
            if(index < 0){
                index += cap;
            }
            return arr[index];
        }
    }
    //reverse functionality added

    void addEnd(T v) {
        if(reversed){
            reverse();
            addFront(v);
            reverse();
        }
        
        else{
            if (size == cap) {
                cap *= 2;

                T* temparr = new T[cap];

                int index;
                for (int i = 0; i < size; i++) {
                    index = start + i;
                    if (index >= size) {
                        index -= size;
                    }
                    temparr[i] = arr[index];
                }

                delete[] arr;
                arr = temparr;

                start = 0;
                end = size - 1;
            }

            if(size>0){
                int current = end + 1;
                if (current >= cap) {
                    current -= cap;
                }

                arr[current] = v;
                end = current;
            }
            else{
                arr[start] = v;
            }

            size++;
        }
    }

    void addFront(T v) {
        if(reversed){
            reverse();
            addEnd(v);
            reverse();
        }

        else{
            if (size == cap) {
                cap *= 2;

                T* temparr = new T[cap];

                int index;
                for (int i = 0; i < size; i++) {
                    index = (start + i)%size;
                    /*if (index >= cap) {
                        index -= cap;
                    }*/
                    temparr[i] = arr[index];
                }

                delete[] arr;
                arr = temparr;

                start = 0;
                end = size - 1;

            }

            if(size > 0){
                int current = start - 1;
                if (current < 0) {
                    current += cap;
                }

                arr[current] = v;
                start = current;
            }
            else{
                arr[start] = v;
            }

            size++;
        }
    }

    void delEnd() {
        if(reversed){
            reverse();
            delFront();
            reverse();
        }
        
        else{
            size--;
            int current = end - 1;
            if (current < 0) {
                current += cap;
            }
            end = current;

            if ((double(size) / double(cap)) <= 0.25) {
                cap /= 2;

                T* temparr = new T[cap];

                int index;
                for (int i = 0; i < size; i++) {
                    index = start + i;
                    if (index >= cap) {
                        index -= cap;
                    }
                    temparr[i] = arr[index];
                }

                delete[] arr;
                arr = temparr;

                start = 0;
                end = size - 1;
            }
        }
    }

    void delFront() {
        if(reversed){
            reverse();
            delEnd();
            reverse();
        }
        
        else{
            size--;
            int current = start + 1;
            if (current >= cap) {
                current -= cap;
            }
            start = current;

            if ((double(size) / double(cap)) <= 0.25) {
                cap /= 2;

                T* temparr = new T[cap];

                int index;
                for (int i = 0; i < size; i++) {
                    index = start + i;
                    if (index >= size) {
                        index -= size;
                    }
                    temparr[i] = arr[index];
                }

                delete[] arr;
                arr = temparr;

                start = 0;
                end = size - 1;
            }
        }
    }

    int length() {
        return size;
    }
    //no reverse functionality required

    int capacity() {
        return cap;
    }
    //no reverse functionality required

    void clear() {
        T* temparr = new T[2];

        delete[] arr;
        arr = temparr;

        start = 0;
        end = 0;
        cap = 2;
        size = 0;
        reversed = false;
    }
    //no reverse functionality required

    int partition(T arr[], int l, int r){
        srand((unsigned) time(NULL));
        int randomnumbah = (l + (rand()%(r-l+1)))%cap; 
        T x = arr[randomnumbah];
        swap(arr[randomnumbah], arr[r]);
        int i = l;
        for (int j = l; j <= r - 1; j++) {
            if (arr[j] <= x) {
                swap(arr[i], arr[j]);
                i++;
            }
        }
        swap(arr[i], arr[r]);
        return i;
    }
  

    T kthSmallest(T arr[], int l, int r, int k){
        int index = partition(arr, l, r);
    
        if (index - l == k - 1){
            return arr[index];
        }
    
        else if (index - l > k - 1) {
            return kthSmallest(arr, l, index - 1, k);
        }
    
        else{
            return kthSmallest(arr, index + 1, r, k - index + l - 1);
        }

    }
    
    T QuickSelect(int k) {
        bool wasReversed = false;
        if(reversed){
            wasReversed = true;
            reverse();
        }
        
        T* temparr = new T[cap];

        int index;
        for (int i = 0; i < size; i++) {
            index = start + i;
            if (index >= cap) {
                index -= cap;
            }
            temparr[i] = arr[index];
        }

        int falseStart = 0;
        int falseEnd = size-1;

        T smallest = kthSmallest(temparr, falseStart, falseEnd, k);

        delete[] temparr;

        if(wasReversed){
            reverse();
        }

        return smallest;

    }

    void merge(T arr1[], int start, int mid, int end) {

        int n1 = mid - start + 1;
        int n2 = end - mid;

        T L[n1], M[n2];

        for (int i = 0; i < n1; i++){
            L[i] = arr1[start + i];
        }
        for (int j = 0; j < n2; j++){
            M[j] = arr1[mid + 1 + j];
        }

        int i = 0;
        int j = 0;
        int k = start;

        while (i < n1 && j < n2) {
            if (L[i] <= M[j]) {
                arr1[k] = L[i];
                i++;
            } else {
                arr1[k] = M[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr1[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr1[k] = M[j];
            j++;
            k++;
        }
    }

    void mergeSort(T arr1[], int left, int right) {
        if (left < right) {
            int mid = left + (right - left) / 2;

            mergeSort(arr1, left, mid);
            mergeSort(arr1, mid + 1, right);

            merge(arr1, left, mid, right);
        }
    }

    void stableSort() {
        if(reversed){
            reverse();
        }
        T* temparr = new T[cap];

        int index;
        for (int i = 0; i < size; i++) {
            index = start + i;
            if (index >= cap) {
                index -= cap;
            }
            temparr[i] = arr[index];
        }

        delete[] arr;
        arr = temparr;

        start = 0;
        end = size - 1;

        mergeSort(arr, start, end);
    }
    //reverse functionality has been implemented

    int linearSearch(T e) {
        int index;
        if(!reversed){
            for (int i = 0; i < size; i++) {
                index = start + i;
                if (index >= cap) {
                    index -= cap;
                }
                if (arr[index] == e) {
                    return i;
                }
            }
        }
        else{
            for(int i = 0; i<size; i++) {
                index = start - i;
                if(index <0){
                    index += cap;
                }
                if(arr[index] == e){
                    return i;
                }
            }
        }
        return -1;
    }
    //reverse functionality has been implemented

    int binarySearch(T arr1[], int start, int end, T comp, int cap) {
        if (start <= end) {
            int mid = (start + end) / 2;
            if (arr1[mid % cap] == comp)
                return mid % cap;
            if (arr1[mid % cap] > comp){
                return binarySearch(arr1, start, mid - 1, comp, cap);
            }
            if (arr1[mid % cap] < comp){
                return binarySearch(arr1, mid + 1, end, comp, cap);
            }
        }
        return -1;
    }

    int binSearch(T e) {
        int wasReversed = false;
        if(reversed){
            reverse();
            wasReversed = true;
        }
        int fakeEnd = end;
        if(end < start){
            fakeEnd+=cap;
        }
        int answer = binarySearch(arr, start, fakeEnd, e, cap);
        if(wasReversed){
            reverse();
        }
        return answer;
    }
    //binsearch reverse functionality added


    void reverse() {
        if(!reversed){
            reversed = true;
        }
        else{
            reversed = false;
        }
        int temp = start;
        start = end;
        end = temp;
    }

};