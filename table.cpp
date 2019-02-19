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
    return std::string();
  }
  else {
    for (std::size_t i = 0; i < hashTable[index].size(); i++){
      if (hashTable[index][i].get_key() == key){
	std::string output = hashTable[index][i].get_data();
	return output;
      }
      else
	return std::string();
    }
  }
  return std::string();
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
  }
  return false;
}

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
  
  mergeSort(vector1);
  
  for(Entry k: vector1){
    out << k << std::endl;
  }
  return out;
}
