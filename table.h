// Andrew Cizas
// table.h
// W19 - Lab05
// 1:00-1:50 pm
#ifndef table_h
#define table_h
#include "entry.h"
#include <string>
#include <iostream>
#include <vector>

class Table {
 
 public:

  // Constructor
  Table(unsigned int max_entries = 100);

  // Constructor by input stream
  Table(unsigned int entries, std::istream& input);

  // Destructor
  ~Table();
  
  // Copy constructor
  Table(const& Table);
  
  // Assignment operator
  Table& operator=(const Table&);

  // Returns the size of the Hash Table
  int getSize() const;

  // Returns max entries
  int getMax_Entries() const;

  // Creates new entry and puts it in the table
  void put(unsigned int key, std::string data);

  // Creates a copy of the parameter in the table and puts it in the table
  void put(Entry e);

  // Returns a string associated with the parameter
  std::string get(unsigned int key) const;
  
  // Removes an entry with the given key
  bool remove(unsigned int key);

  // Overloads the << operator to output entries on separate lines
  friend std::ostream& operator<< (std::ostream& out, const Table& t);

 private:
  int size;
  size_t num_entries;
  typedef std::vector<std::vector<Entry> > entry;
  std::vector<std::vector<Entry> > hashTable;
  size_t hashingFunction(int key){
    return key%size;
  }
  size_t hashingFunction(int key) const {
    return key%size;
  }
  
};

//void mergeSort(Entry data[], size_t tableSize);
//void merge(Entry data[], size_t n1, size_t n2);

//void mergeSort(std::vector<Entry>& A);
//void merge(std::vector<Entry>& A, std::vector<Entry>& array1,std::vector<Entry>& array2);

void mergeSort(std::vector<Entry> in, int l, int r);
void merge(std::vector<Entry> in, int l, int m, int r);
#endif /* table_h */




