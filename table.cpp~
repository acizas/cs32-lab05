// table.cpp

#include <vector>
#include <iostream>
#include "entry.h"
#include <sstream>
#include "table.h"
#include <string>
#include <iterator>

Table::Table(unsigned int max_entries) {

  num_entries = 0;
  size = max_entries;
  hashTable.resize(size);
   
}

Table::Table(unsigned int entries, std::istream& input) {

    size = entries;
    hashTable.resize(size);
    num_entries = entries;
    Entry a;
    for (int i = 0; i < entries; i++){
      input >> a;
      put(a);
    } 
  }

Table::Table(const& Table) {

  size = Table.getSize();
  hashTable.resize(size);
  for (int i = 0; i < Table.getMax_Entries()-1; i++) {
    Entry a(Table[i]);
    put(a);
  }
}

Table::~Table() {
  /*
  for (int i = 0; i < size; i++) {
    int index = hashingFunction(i);
    if (hashTable[index])
      delete hashTable[index];
    delete[] hashTable;
  */
  
  while(!hashTable.empty())
    hashTable.pop_back();
}

Table& operator=(const Table&) {

  while(!hashTable.empty())
    hashTable.pop_back();
  
  size = Table.getSize();
  hashTable.resize(size);
  for (int i = 0; i < Table.getMax_Entries()-1; i++) {
    Entry a(Table[i]);
    put(a);
  }

}
  
int Table::getSize() const {

  return size;

}

int Table::getMax_Entries() const {

  return num_entries;

}

void Table::put(unsigned int key, std::string data) {

  Entry e;
  e.set_key(key);
  e.set_data(data);
  put(e);
  num_entries++;
  
}

void Table::put(Entry e) {

  unsigned int index = hashingFunction(e.get_key());
  if (!hashTable[index].empty()){
    for (std::size_t i = 0; i < hashTable[index].size(); i++){
      if (hashTable[index][i].get_key() == e.get_key()){
	  hashTable[index][i] = e;
	  return;
	}
    }
  }
  
  else {
    hashTable[index].push_back(e);
    num_entries++;
  }
}

std::string Table::get(unsigned int key) const {

  unsigned int index = hashingFunction(key);
  if (hashTable[index].size() == 0){
    return "";
  }
  else {
    for (std::size_t i = 0; i < hashTable[index].size(); i++){
      if (hashTable[index][i].get_key() == key){
	return hashTable[index][i].get_data();
      }
      else
	return "";
    }
  }
}

/*
  while(hashTable[index] != '\0' && hashTable[index]->get_key() != key){
    index = (index + 1)&size;
  }
  if (hashTable[index]== '\0')
    return 0;
  else
    return hashTable[index]->get_data();
}
*/

bool Table::remove(unsigned int key) {

  unsigned int index = hashingFunction(key);
  for (int i = 0; i < hashTable[index].size(); i++) {
    if (hashTable[index][i].get_key() == key){
      std::swap(hashTable[index][i],
		hashTable[index][hashTable[index].size()-1]);
      hashTable[index].pop_back();
      num_entries--;
      return true;
    }
    else
      return false;
  }
}

void merge(vector<Entry>& A, int p, int q, int r)
{
    //n1 and n2 are the lengths of the pre-sorted sublists, A[p..q] and A[q+1..r]
    int n1=q-p+1;
    int n2=r-q;
    //copy these pre-sorted lists to L and R

    vector<Entry> L(&A[p],&A[q+1]);
    vector<Entry> R(&A[q+1],&A[r+1]);


    //Create a sentinal value for L and R that is larger than the largest
    //element of A
    int largest;
    if(L[n1-1].get_key()<R[n2-1].get_key()) largest=R[n2-1].get_key(); else largest=L[n1-1];
    L.push_back(largest+1);
    R.push_back(largest+1);

    //Merge the L and R lists
    int i=0;
    int j=0;
    for(int k=p; k<=r; k++)
    {
      if (L[i].get_key()<=R[j].get_key())
        {
            A[k]=L[i];
            i++;
        } else
        {
            A[k]=R[j];
            j++;
        }
    }
}


void mergeSort(vector<Entry>& A, int p, int r)
{
    //This recursively splits the vector A into smaller sections 
    if(p<r)
    {
        int q=floor((p+r)/2);
        mergeSort(A,p,q);
        mergeSort(A,q+1,r);
        merge(A,p,q,r);
    }

}    

      
/*
void mergeSort(std::vector<Entry>& A) {

  if (1 < A.size()){
    std::vector<Entry> array1(A.begin(), A.begin() + A.size() / 2);
    //std::cout << "Iterator 1" << std::endl;
    mergeSort(array1);
    //std::cout << "Mergesort 1" << std::endl;
    std::vector<Entry> array2(A.begin() + A.size()/2, A.end());
    //std::cout << "Iterator 2" << std::endl;
    mergeSort(array2);
    //std::cout << "Mergesort 2" << std::endl;
    merge(A, array1, array2);
    //std::cout << "Merge" << std::endl;
  }
  
}

void merge(std::vector<Entry>& A, std::vector<Entry>& array1,
		     std::vector<Entry>& array2){
  int i, j, k;
  for (i = 0, j = 0, k = 0; i < array1.size() && j < array2.size(); k++){
    if ((((array1.at(i)).get_key())%(A.size()))
	<= (((array2.at(j)).get_key()%(A.size())))){
      A.push_back(array1.at(i));
      i++;
    }
    else if ((((array1.at(i)).get_key())%(A.size()))
	     > (((array2.at(j)).get_key()%(A.size())))){
      A.push_back(array2.at(j));
     
      j++;
    }
    k++;
  }

  while (i < array1.size()){
    A.push_back(array2.at(j));
    i++;
  }

  while (j < array2.size()){
    A.push_back(array2.at(j));
    j++;
  }
}
*/

std::ostream& operator<< (std::ostream& out, const Table& t) {

  
  std::vector<Entry> vector1(t.num_entries);
  for (int i = 0; i < t.hashTable.size(); i++){
    for (int j = 0; j < t.hashTable[i].size(); j++) {
      vector1.push_back(t.hashTable[i][j]);
    }
  }
  
  mergeSort(vector1, 0, vector1.size()-1);
  
  for(Entry k: vector1){
    out << k << std::endl;
  }
  return out;
}
