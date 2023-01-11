/**
 * @file util.h
 */

/*************************************************************************/
/* Stanford Portable Library                                             */
/* Copyright (c) 2014 by Eric Roberts <eroberts@cs.stanford.edu>         */
/*                                                                       */
/* Modified by Jeff Lutgen <jlutgen@whittier.edu> 2022                   */
/*                                                                       */
/* This program is free software: you can redistribute it and/or modify  */
/* it under the terms of the GNU General Public License as published by  */
/* the Free Software Foundation, either version 3 of the License, or     */
/* (at your option) any later version.                                   */
/*                                                                       */
/* This program is distributed in the hope that it will be useful,       */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of        */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         */
/* GNU General Public License for more details.                          */
/*                                                                       */
/* You should have received a copy of the GNU General Public License     */
/* along with this program.  If not, see <http://www.gnu.org/licenses/>. */
/*************************************************************************/

#ifndef _util_h
#define _util_h

static const int HASH_SEED = 5381;               // Starting point for first cycle
static const int HASH_MULTIPLIER = 33;           // Multiplier for each cycle
static const int HASH_MASK = unsigned(-1) >> 1;  // All 1 bits except the sign

#include <string>

/**
 * @class ErrorException
 *
 * @brief An %ErrorException is thrown by calls to the \ref error
 * function.
 *
 * Typical code for catching errors looks like this:
 *
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *    try {
 *       ... code in which an error might occur ...
 *    } catch (ErrorException & ex) {
 *       ... code to handle the error condition ...
 *    }
 *   ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 *
 * If an %ErrorException is thrown at any point in the
 * range of the <code>try</code> (including in functions called from
 * that code), control will jump immediately to the error-handling code.
 */
// class ErrorException : public std::exceptioVn {
// public:
//    ErrorException(std::string msg);
//    virtual ~ErrorException() throw ();
//    virtual std::string getMessage() const;
//    virtual const char *what() const throw ();

// private:
//    std::string msg;
// };

/**
 * Prints an error message and exits the program.
 */
void error(std::string msg);

/**
 * Pause the program for given number of milliseconds.
 */
void pause_ms(int millis);

#include <string>

/** \_overload */
bool startsWith(const std::string& str, const char prefix);
/**
 * Returns \c true if the string \em str starts with
 * the specified prefix, which may be either a string or a character.
 *
 * Sample usage:
 *
 *     if (startsWith(str, prefix)) ...
 */
bool startsWith(const std::string& str, const std::string& prefix);

/**
 * Returns a new character in which the given uppercase character has been
 * converted into its lowercase equivalent.
 */
char toLowerCase(char ch);

/**
 * Returns a new string in which all uppercase characters have been converted
 * into their lowercase equivalents.
 */
std::string toLowerCase(const std::string& str);

/**
 * Modifies the given string in-place such that all uppercase characters have
 * been converted into their lowercase equivalents.
 */
void toLowerCaseInPlace(std::string& str);

/**
 * Returns a new character in which the given lowercase character has been
 * converted into its uppercase equivalent.
 */
char toUpperCase(char ch);

/**
 * Returns a new string in which all lowercase characters have been converted
 * into their uppercase equivalents.
 */
std::string toUpperCase(const std::string& str);

/**
 * Modifies the given string in-place such that all lowercase characters have
 * been converted into their uppercase equivalents.
 */
void toUpperCaseInPlace(std::string& str);

/**
 * Returns a new string after removing any whitespace characters
 * from the beginning and end of the argument.
 */
std::string trim(const std::string& str);

/**
 * Modifies the given string in-place where any whitespace characters
 * from the beginning and end of the argument are removed.
 */
void trimInPlace(std::string& str);

/**
 * Returns a new string after removing any whitespace characters
 * from the end of the argument.
 */
std::string trimEnd(const std::string& str);

/**
 * Modifies the given string in-place to remove any whitespace characters
 * from its end.
 */
void trimEndInPlace(std::string& str);

/**
 * Returns a new string after removing any whitespace characters
 * from the beginning of the argument.
 */
std::string trimStart(const std::string& str);

/**
 * Modifies the given string in-place to remove removing any whitespace
 * characters from the beginning of it.
 */
void trimStartInPlace(std::string& str);

/**
 * Reads a complete line from the \c cin stream and scans it as an
 * integer. If the scan succeeds, the integer value is returned. If
 * the argument is not a legal integer or if extraneous characters
 * (other than whitespace) appear in the string, the user is given
 * a chance to reenter the value. If supplied, the optional
 * \em prompt string is printed before reading the value.
 *
 * Sample usage:
 *
 *     int n = getInteger(prompt);
 */
int getInteger(std::string prompt = "");

/**
 * Reads a complete line from the \c cin stream  and scans it as a
 * floating-point number. If the scan succeeds, the floating-point
 * value is returned.  If the input is not a legal number or if
 * extraneous characters (other than whitespace) appear in the string,
 * the user is given a chance to reenter the value. If supplied, the
 * optional \em prompt string is printed before reading the value.
 *
 * Sample usage:
 *
 *     double x = getReal(prompt);
 */
double getReal(std::string prompt = "");

/**
 * Reads a line of text from the \em cin stream and returns that line
 * as a string.  The newline character that terminates the input is
 * not stored as part of the return value.  If supplied, the optional
 * \em prompt string is printed before reading the value.
 *
 * Sample usage:
 *
 *     string line = getLine(prompt);
 */
std::string getLine(std::string prompt = "");

/**
 * @file lexicon.h
 *
 * @brief
 * This file exports the Lexicon class, which is a
 * compact structure for storing a list of words.
 */

#include <string>
#include <cctype>
#include <stack>
#include <set>

/**
 * @class Lexicon
 *
 * @brief This class represents a <b><i>lexicon,</i></b> or word list.
 *
 * The main difference between a lexicon and a dictionary is that
 * a lexicon does not provide any mechanism for storing definitions;
 * the lexicon contains only words, with no associated information.
 * It is similar to a set of strings, but with a more
 * space-efficient internal representation.  This class
 * supports efficient lookup operations for words and prefixes.
 *
 * As an example of the use of the `%Lexicon` class, the
 * following program lists all the two-letter words in the lexicon
 * stored in the file <code>EnglishWords.dat</code>:
 *
 * ~~~
 *    int main() {
 *       Lexicon english("EnglishWords.dat");
 *       for (string word : english) {
 *          if (word.length() == 2) {
 *             cout << word << endl;
 *          }
 *       }
 *       return 0;
 *    }
 * ~~~
 */
class Lexicon {

public:

/** \_overload */
    Lexicon();
/**
 * Initializes a new lexicon.  The default constructor creates an empty
 * lexicon.  The second form reads in the contents of the lexicon from
 * the specified data file.  The data file must be in one of two formats:
 * <ol>
 *  <li>A space-efficient precompiled binary format, or
 *  <li>A text file containing one word per line.
 * </ol>
 * The Stanford-Whittier library distribution
 * includes a binary lexicon file named <code>EnglishWords.dat</code>
 * containing more than 127,000 English words.  The standard code pattern
 * to initialize that lexicon looks like this:
 *
 * ~~~
 *    Lexicon english("EnglishWords.dat");
 * ~~~
 *
 * Sample usages:
 *
 *     Lexicon lex;
 *     Lexicon lex(filename);
 */
   Lexicon(std::string filename);


/**
 * Deallocates any storage associated with this lexicon.
 */
   virtual ~Lexicon();


/**
 * Compares two lexicons for equality.
 * Identical in behavior to the \c == operator.
 *
 * Sample usage:
 *
 *      if (lex1.equals(lex2)) ...
 */
    bool equals(const Lexicon& lex2) const;


/**
 * Returns the number of words contained in this lexicon.
 *
 * Sample usage:
 *
 *     int n = lex.size();
 */
   int size() const;


/**
 * Returns \c true if this lexicon contains no words.
 *
 * Sample usage:
 *
 *     if (lex.isEmpty()) ...
 */
   bool isEmpty() const;


/**
 * Removes all words from the lexicon.
 *
 * Sample usage:
 *
 *     lex.clear();
 */
   void clear();


/**
 * Adds the specified word to the lexicon.
 *
 * Sample usage:
 *
 *     lex.add(word);
 */
   void add(std::string word);


/**
 * Reads a file and adds all of its words to the lexicon.
 * The file must be in one of the two formats specified in the
 * description of the Lexicon class. Moreover, if the file is in
 * the binary format, this lexicon must be empty when this method
 * is called or this method will signal an error.
 *
 * Sample usage:
 *
 *     lex.addWordsFromFile(filename);
 */
   void addWordsFromFile(std::string filename);


/**
 * Returns \c true if \em word is contained in this
 * lexicon.  In the `%Lexicon` class, the case of letters is
 * ignored, so "Zoo" is the same as "ZOO" or "zoo".
 *
 * Sample usage:
 *
 *     if (lex.contains(word)) ...
 */
   bool contains(std::string word) const;


/**
 * Returns \c true if any words in this lexicon begin with the string \em prefix.
 * Like \ref contains, this method ignores the case of letters
 * so that "MO" is a prefix of both "monkey" and "Monday".
 *
 * Sample usage:
 *
 *     if (lex.containsPrefix(prefix)) ...
 */
   bool containsPrefix(std::string prefix) const;


/**
 * Calls the specified function on each word in this lexicon.
 *
 * Sample usage:
 *
 *     lexicon.mapAll(fn);
 */
   void mapAll(void (*fn)(std::string)) const;
   void mapAll(void (*fn)(const std::string &)) const;
   template <typename FunctorType>
   void mapAll(FunctorType fn) const;


    /** \_overload */ // Not really. Just a comment-hack for Doxygen.
    bool operator !=(const Lexicon& lex2) const;
/*
 * Relational operators to compare two lexicons to see if they have the same elements.
 *
 * Sample usages:
 *
 *      if (lex1 == lex2) ...
 *      if (lex1 != lex2) ...
 */
    bool operator ==(const Lexicon& lex2) const;


/*
 * Additional Lexicon operations
 * -----------------------------
 * In addition to the methods listed in this interface, the Lexicon
 * class supports the following operations:
 *
 *   - Deep copying for the copy constructor and assignment operator
 *   - Iteration using the range-based for statement and STL iterators
 *
 * All iteration is guaranteed to proceed in alphabetical order.  All
 * words in the lexicon are stored in lowercase.
 */

/* Private section */

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

private:

#ifdef _WIN32
#ifndef LITTLE_ENDIAN
#define LITTLE_ENDIAN 1
#endif
#ifndef BYTE_ORDER
#define BYTE_ORDER LITTLE_ENDIAN
#endif
#endif

#pragma pack(push, 1)
   struct Edge {
#if defined(BYTE_ORDER) && BYTE_ORDER == LITTLE_ENDIAN
      unsigned long letter:5;
      unsigned long lastEdge:1;
      unsigned long accept:1;
      unsigned long unused:1;
      unsigned long children:24;
#else
      unsigned long children:24;
      unsigned long unused:1;
      unsigned long accept:1;
      unsigned long lastEdge:1;
      unsigned long letter:5;
#endif
   };
#pragma pack(pop)

   Edge *edges, *start;
   int numEdges, numDawgWords;
   std::set<std::string> otherWords;

public:

/*
 * Deep copying support
 * --------------------
 * This copy constructor and operator= are defined to make a
 * deep copy, making it possible to pass/return lexicons by value
 * and assign from one lexicon to another.  The entire contents of
 * the lexicon, including all words, are copied.  Making copies is
 * generally avoided because of the expense and thus, lexicons are
 * typically passed by reference.  When a copy is needed, these
 * operations are supported.
 */

   Lexicon(const Lexicon & src);
   Lexicon & operator=(const Lexicon & src);

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator : public std::iterator<std::input_iterator_tag,std::string> {
   private:
      const Lexicon *lp;
      int index;
      std::string currentDawgPrefix;
      std::string currentSetWord;
      std::string tmpWord;
      Edge *edgePtr;
      std::stack<Edge *> stack;
      std::set<std::string>::iterator setIterator;
      std::set<std::string>::iterator setEnd;

      void advanceToNextWordInDawg();
      void advanceToNextWordInSet();
      void advanceToNextEdge();

   public:
      iterator() {
         this->lp = NULL;
      }

      iterator(const Lexicon *lp, bool endFlag) {
         this->lp = lp;
         if (endFlag) {
            index = lp->size();
         } else {
            index = 0;
            edgePtr = NULL;
            setIterator = lp->otherWords.begin();
            setEnd = lp->otherWords.end();
            currentDawgPrefix = "";
            currentSetWord = "";
            advanceToNextWordInDawg();
            advanceToNextWordInSet();
         }
      }

      iterator(const iterator & it) {
         lp = it.lp;
         index = it.index;
         currentDawgPrefix = it.currentDawgPrefix;
         currentSetWord = it.currentSetWord;
         edgePtr = it.edgePtr;
         stack = it.stack;
         setIterator = it.setIterator;
      }

      iterator & operator++() {
         if (edgePtr == NULL) {
            advanceToNextWordInSet();
         } else {
            if (currentSetWord == "" || currentDawgPrefix < currentSetWord) {
               advanceToNextWordInDawg();
            } else {
               advanceToNextWordInSet();
            }
         }
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return lp == rhs.lp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      std::string operator*() {
         if (edgePtr == NULL) return currentSetWord;
         if (currentSetWord == "" || currentDawgPrefix < currentSetWord) {
            return currentDawgPrefix + lp->ordToChar(edgePtr->letter);
         } else {
            return currentSetWord;
         }
      }

      std::string *operator->() {
         if (edgePtr == NULL) return &currentSetWord;
         if (currentSetWord == "" || currentDawgPrefix < currentSetWord) {
            tmpWord = currentDawgPrefix + lp->ordToChar(edgePtr->letter);
            return &tmpWord;
         } else {
            return &currentSetWord;
         }
      }

   };

   iterator begin() const {
      return iterator(this, false);
   }

   iterator end() const {
      return iterator(this, true);
   }

private:

   Edge *findEdgeForChar(Edge *children, char ch) const;
   Edge *traceToLastEdge(const std::string & s) const;
   void readBinaryFile(std::string filename);
   void deepCopy(const Lexicon & src);
   int countDawgWords(Edge *start) const;

   unsigned int charToOrd(char ch) const {
      return ((unsigned int)(tolower(ch) - 'a' + 1));
   }

   char ordToChar(unsigned int ord) const {
      return ((char)(ord - 1 + 'a'));
   }
   friend std::ostream& operator <<(std::ostream& os, const Lexicon& lex);
};

template <typename FunctorType>
void Lexicon::mapAll(FunctorType fn) const {
   for (std::string word : *this) {
      fn(word);
   }
}

/*
 * Hashing function for lexicons
 */
int hashCode(const Lexicon& l);

/**
 * Overloads the `<<` operator so that it is able
 * to display lexicons.
 *
 * Sample usage:
 *
 *     cout << lex;
 */
std::ostream& operator <<(std::ostream& os, const Lexicon& lex);

// Grid ---------------------------------------------------------

#include <sstream>
#include <vector>

/**
 * @class Grid
 *
 * @brief This class stores an indexed, two-dimensional array.
 *
 * The following code, for example, creates an identity matrix
 * of size \em n, in which the elements are 1.0 along the main
 * diagonal and 0.0 everywhere else:
 *
 * ~~~
 *    Grid<double> createIdentityMatrix(int n) {
 *       Grid<double> matrix(n, n);
 *       for (int i = 0; i < n; i++) {
 *          matrix[i][i] = 1.0;
 *       }
 *       return matrix;
 *    }
 * ~~~
 */

template <typename ValueType>
class Grid {

public:

/* Forward references */
   class GridRow;
   class GridRowConst;


/** \_overload */
   Grid();
/**
 * Initializes a new grid.  The second form of the constructor is
 * more common and creates a grid with the specified number of rows
 * and columns.  Each element of the grid is initialized to the
 * default value for the type.  The default constructor creates an
 * empty grid for which the client must call \ref resize to set the
 * dimensions.
 *
 * Sample usages:
 *
 *     Grid<ValueType> grid;
 *     Grid<ValueType> grid(nRows, nCols);
 */
   Grid(int nRows, int nCols);


/**
 * Frees any heap storage associated with this grid.
 */
   virtual ~Grid();


/**
 * Returns the number of rows in this grid.
 *
 * Sample usage:
 *
 *     int nRows = grid.numRows();
 */
   int numRows() const;


/**
 * Returns the number of columns in this grid.
 *
 * Sample usage:
 *
 *     int nCols = grid.numCols();
 */
   int numCols() const;


/**
 * Reinitializes this grid to have the specified number of rows
 * and columns.  If the optional \em retain parameter is \c true,
 * the previous grid contents are retained as much as possible.
 * If \em retain is not passed or is \c false, any previous grid contents
 * are discarded.
 *
 * Sample usages:
 *
 *     grid.resize(nRows, nCols);
 *     grid.resize(nRows, nCols, retain);
 */
   void resize(int nRows, int nCols, bool retain = false);


/**
 * Returns \c true if this grid contains exactly the same
 * values as the given other grid.
 * Identical in behavior to the == operator.
 *
 * Sample usage:
 *
 *      if (grid.equals(grid2)) ...
 */
   bool equals(const Grid<ValueType>& grid2) const;


/**
  * Stores the given value in every cell of this grid.
  *
  * Sample usage:
  *
  *     grid.fill(value);
  */
   void fill(const ValueType& value);


/**
 * Returns \c true if the specified row and column position
 * is inside the bounds of the grid.
 *
 * Sample usage:
 *
 *     if (grid.inBounds(row, col)) ...
 */
   bool inBounds(int row, int col) const;


/**
 * Returns the element at the specified (\em row, \em col)
 * location in this grid.  This method signals an error if the
 * specified location is outside the grid boundaries.
 *
 * Sample usage:
 *
 *     ValueType value = grid.get(row, col);
 */
   ValueType get(int row, int col);
   const ValueType & get(int row, int col) const;


/**
 * Replaces the element at the specified (\em row, \em col)
 * location in this grid with a new value.  This method signals an error
 * if the specified location is outside the grid boundaries.
 *
 * Sample usage:
 *
 *     grid.set(row, col, value);
 */
   void set(int row, int col, ValueType value);


/**
 * Overloads the <code>[]</code> operator to select elements from this grid.
 * This extension enables the use of traditional array notation to
 * get or set individual elements.  This method signals an error if
 * the specified location is outside
 * the grid boundaries.
 *
 * Sample usage:
 *
 *      grid[row][col]
 */
   GridRow operator[](int row);
   const GridRowConst operator [](int row) const;


/**
 * Returns a printable string representation of this grid.
 *
 * Sample usage:
 *
 *     string str = grid.toString();
 */
   std::string toString();


/**
 * Calls the specified function on each element of this grid.  The
 * elements are processed in <b><i>row-major order</i></b>, in which
 * all the elements of row 0 are processed, followed by the elements
 * in row 1, and so on.
 *
 * Sample usage:
 *
 *     grid.mapAll(fn);
 */
   void mapAll(void (*fn)(ValueType value)) const;
   void mapAll(void (*fn)(const ValueType & value)) const;
   template <typename FunctorType>
   void mapAll(FunctorType fn) const;


/*
 * Additional Grid operations
 * --------------------------
 * In addition to the methods listed in this interface, the Grid
 * class supports the following operations:
 *
 *   - Stream I/O using the << and >> operators
 *   - Deep copying for the copy constructor and assignment operator
 *   - Iteration using the range-based for statement and STL iterators
 *
 * The iteration forms process the grid in row-major order.
 */

/**
 * Compares two grids for equality.
 *
 * Sample usage:
 *
 *      if (grid1 == grid2) ...
 */
   bool operator ==(const Grid& grid2) const;


/**
 * Compares two grids for inequality.
 *
 * Sample usage:
 *
 *     if (grid1 != grid2) ...
 */
   bool operator !=(const Grid& grid2) const;

/* Private section */

private:

/**********************************************************************/
/* Note: Everything below this point in the file is logically part    */
/* of the implementation and should not be of interest to clients.    */
/**********************************************************************/

/*
 * Implementation notes: Grid data structure
 * -----------------------------------------
 * The Grid is internally managed as a dynamic array of elements.
 * The array itself is one-dimensional, the logical separation into
 * rows and columns is done by arithmetic computation.  The layout
 * is in row-major order, which is to say that the entire first row
 * is laid out contiguously, followed by the entire second row,
 * and so on.
 */

/* Instance variables */

   ValueType *elements;  /* A dynamic array of the elements   */
   int nRows;            /* The number of rows in the grid    */
   int nCols;            /* The number of columns in the grid */

/* Private method prototypes */

   void checkRange(int row, int col);

/*
 * Hidden features
 * ---------------
 * The remainder of this file consists of the code required to
 * support deep copying and iteration.  Including these methods
 * in the public interface would make that interface more
 * difficult to understand for the average client.
 */

/*
 * Deep copying support
 * --------------------
 * This copy constructor and operator= are defined to make a
 * deep copy, making it possible to pass/return grids by value
 * and assign from one grid to another.  The entire contents of
 * the grid, including all elements, are copied.  Each grid
 * element is copied from the original grid to the copy using
 * assignment (operator=).  Making copies is generally avoided
 * because of the expense and thus, grids are typically passed
 * by reference, however, when a copy is needed, these operations
 * are supported.
 */

   void deepCopy(const Grid & grid) {
      int n = grid.nRows * grid.nCols;
      elements = new ValueType[n];
      for (int i = 0; i < n; i++) {
         elements[i] = grid.elements[i];
      }
      nRows = grid.nRows;
      nCols = grid.nCols;
   }

public:

   Grid & operator=(const Grid & src) {
      if (this != &src) {
         delete[] elements;
         deepCopy(src);
      }
      return *this;
   }

   Grid(const Grid & src) {
      deepCopy(src);
   }

/*
 * Iterator support
 * ----------------
 * The classes in the StanfordCPPLib collection implement input
 * iterators so that they work symmetrically with respect to the
 * corresponding STL classes.
 */

   class iterator : public std::iterator<std::input_iterator_tag, ValueType> {

   public:

      iterator(const Grid *gp, int index) {
         this->gp = gp;
         this->index = index;
      }

      iterator(const iterator & it) {
         this->gp = it.gp;
         this->index = it.index;
      }

      iterator & operator++() {
         index++;
         return *this;
      }

      iterator operator++(int) {
         iterator copy(*this);
         operator++();
         return copy;
      }

      bool operator==(const iterator & rhs) {
         return gp == rhs.gp && index == rhs.index;
      }

      bool operator!=(const iterator & rhs) {
         return !(*this == rhs);
      }

      ValueType & operator*() {
         return gp->elements[index];
      }

      ValueType *operator->() {
         return &gp->elements[index];
      }

   private:
      const Grid *gp;
      int index;
   };

   iterator begin() const {
      return iterator(this, 0);
   }

   iterator end() const {
      return iterator(this, nRows * nCols);
   }

/*
 * Private class: Grid<ValType>::GridRow
 * -------------------------------------
 * This section of the code defines a nested class within the Grid template
 * that makes it possible to use traditional subscripting on Grid values.
 */

   class GridRow {
   public:
      GridRow() {
         /* Empty */
      }

      ValueType & operator[](int col) {
         extern void error(std::string msg);
         if (!gp->inBounds(row, col)) {
            error("Grid::operator [][]: Grid index values out of range");
         }
         return gp->elements[(row * gp->nCols) + col];
      }

      ValueType operator[](int col) const {
         extern void error(std::string msg);
         if (!gp->inBounds(row, col)) {
            error("Grid::operator [][]: Grid index values out of range");
         }
         return gp->elements[(row * gp->nCols) + col];
      }

   private:
      GridRow(Grid *gridRef, int index) {
         gp = gridRef;
         row = index;
      }

      Grid *gp;
      int row;
      friend class Grid;
   };
   friend class GridRow;

   class GridRowConst {
   public:
       GridRowConst() : gp(NULL), row(0) {
           /* Empty */
       }

       const ValueType operator [](int col) const {
           extern void error(std::string msg);
           if (!gp->inBounds(row, col)) {
              error("Grid::operator [][]: Grid index values out of range");
           }
           return gp->elements[(row * gp->nCols) + col];
       }

   private:
       GridRowConst(Grid* const gridRef, int index) : gp(gridRef), row(index) {}

       const Grid* const gp;
       const int row;
       friend class Grid;
   };
   friend class GridRowConst;

};

extern void error(std::string msg);

template <typename ValueType>
Grid<ValueType>::Grid() {
   elements = NULL;
   nRows = 0;
   nCols = 0;
}

template <typename ValueType>
Grid<ValueType>::Grid(int nRows, int nCols) {
   elements = NULL;
   resize(nRows, nCols);
}

template <typename ValueType>
Grid<ValueType>::~Grid() {
   if (elements != NULL) delete[] elements;
}

template <typename ValueType>
int Grid<ValueType>::numRows() const {
   return nRows;
}

template <typename ValueType>
int Grid<ValueType>::numCols() const {
   return nCols;
}

template <typename ValueType>
void Grid<ValueType>::resize(int nRows, int nCols, bool retain) {
   if (nRows < 0 || nCols < 0) {
      error("Grid::resize: Attempt to resize grid to invalid size ("
            + std::to_string(nRows) + ", "
            + std::to_string(nCols) + ")");
   }
   // save backup of old array/size
   ValueType* oldElements = this->elements;
   int oldnRows = this->nRows;
   int oldnCols = this->nCols;

   // create new empty array and set new size
   this->nRows = nRows;
   this->nCols = nCols;
   this->elements = new ValueType[nRows * nCols];

   // initialize to empty/default state
   ValueType value = ValueType();
   for (int i = 0; i < nRows * nCols; i++) {
       this->elements[i] = value;
   }

   // possibly retain old contents
   if (retain) {
       int minRows = oldnRows < nRows ? oldnRows : nRows;
       int minCols = oldnCols < nCols ? oldnCols : nCols;
       for (int row = 0; row < minRows; row++) {
           for (int col = 0; col < minCols; col++) {
               this->elements[(row * nCols) + col] = oldElements[(row * oldnRows) + col];
           }
       }
   }

   // free old array memory
   if (oldElements != NULL) {
       delete[] oldElements;
   }
}

template <typename ValueType>
bool Grid<ValueType>::equals(const Grid<ValueType>& grid2) const {
    // optimization: if literally same grid, stop
    if (this == &grid2) {
        return true;
    }

    if (nRows != grid2.nRows || nCols != grid2.nCols) {
        return false;
    }
    for (int row = 0; row < nRows; row++) {
        for (int col = 0; col < nCols; col++) {
            if (get(row, col) != grid2.get(row, col)) {
                return false;
            }
        }
    }
    return true;
}

template <typename ValueType>
void Grid<ValueType>::fill(const ValueType& value) {
    for (int i = 0; i < nRows * nCols; i++) {
        elements[i] = value;
    }
}

template <typename ValueType>
bool Grid<ValueType>::inBounds(int row, int col) const {
   return row >= 0 && col >= 0 && row < nRows && col < nCols;
}

template <typename ValueType>
ValueType Grid<ValueType>::get(int row, int col) {
   if (!inBounds(row, col)) error("Grid::get: Grid indices out of bounds");
   return elements[(row * nCols) + col];
}

template <typename ValueType>
const ValueType & Grid<ValueType>::get(int row, int col) const {
   if (!inBounds(row, col)) error("Grid::get: Grid indices out of bounds");
   return elements[(row * nCols) + col];
}

template <typename ValueType>
void Grid<ValueType>::set(int row, int col, ValueType value) {
   if (!inBounds(row, col)) error("Grid::set: Grid indices out of bounds");
   elements[(row * nCols) + col] = value;
}

template <typename ValueType>
typename Grid<ValueType>::GridRow Grid<ValueType>::operator[](int row) {
   return GridRow(this, row);
}

//template <typename ValueType>
//const typename Grid<ValueType>::GridRow
//               Grid<ValueType>::operator[](int row) const {
//   return GridRow(this, row);
//}

template <typename ValueType>
const typename Grid<ValueType>::GridRowConst
Grid<ValueType>::operator [](int row) const {
    return GridRowConst(const_cast<Grid*>(this), row);
}

template <typename ValueType>
bool Grid<ValueType>::operator ==(const Grid& grid2) const {
    return equals(grid2);
}

template <typename ValueType>
bool Grid<ValueType>::operator !=(const Grid& grid2) const {
    return !equals(grid2);
}

template <typename ValueType>
void Grid<ValueType>::mapAll(void (*fn)(ValueType value)) const {
   for (int i = 0; i < nRows; i++) {
      for (int j = 0; j < nCols; j++) {
         fn(get(i, j));
      }
   }
}

template <typename ValueType>
void Grid<ValueType>::mapAll(void (*fn)(const ValueType & value)) const {
   for (int i = 0; i < nRows; i++) {
      for (int j = 0; j < nCols; j++) {
         fn(get(i, j));
      }
   }
}

template <typename ValueType>
template <typename FunctorType>
void Grid<ValueType>::mapAll(FunctorType fn) const {
   for (int i = 0; i < nRows; i++) {
      for (int j = 0; j < nCols; j++) {
         fn(get(i, j));
      }
   }
}

template <typename ValueType>
std::string Grid<ValueType>::toString() {
   std::ostringstream os;
   os << *this;
   return os.str();
}

/*
 * Implementation notes: << and >>
 * -------------------------------
 * The insertion and extraction operators use the template facilities in
 * strlib.h to read and write generic values in a way that treats strings
 * specially.
 */
/**
 * Overloads the `<<` operator so that it is able
 * to display `%Grid` objects.
 *
 * Sample usage:
 *
 *     cout << grid;
 */
template <typename ValueType>
std::ostream & operator<<(std::ostream & os, const Grid<ValueType> & grid) {
   os << "{";
   int nRows = grid.numRows();
   int nCols = grid.numCols();
   for (int i = 0; i < nRows; i++) {
      if (i > 0) os << ", ";
      os << "{";
      for (int j = 0; j < nCols; j++) {
         if (j > 0) os << ", ";
        //  writeGenericValue(os, grid.get(i, j), true);
        os << grid.get(i, j);
      }
      os << "}";
   }
   return os << "}";
}

// template <typename ValueType>
// std::istream & operator>>(std::istream & is, Grid<ValueType> & grid) {
//    std::vector<vector<ValueType> > vec2d;
//    is >> vec2d;
//    int nRows = vec2d.size();
//    int nCols = (nRows == 0) ? 0 : vec2d[0].size();
//    grid.resize(nRows, nCols);
//    for (int i = 0; i < nRows; i++) {
//       for (int j = 0; j < nCols; j++) {
//          grid[i][j] = vec2d[i][j];
//       }
//    }
//    return is;
// }

/*
 * Template hash function for grids.
 * Requires the element type in the Grid to have a hashCode function.
 */
template <typename T>
int hashCode(const Grid<T>& g) {
    int code = HASH_SEED;
    for (T n : g) {
        code = HASH_MULTIPLIER * code + hashCode(n);
    }
    return int(code & HASH_MASK);
}

#endif