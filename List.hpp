//
//  List.hpp
//  Simulation
//
//  Created by Terence Kelly on 30/09/2020.
//  Copyright © 2020 Park Crescent Consultants. All rights reserved.
//
//  List<T> has two types of functions (operations), Terminal operations and
//  Cumulative operations.  Cumulative operations can be stacked and joined together
//  with each succeeding operation using the results of the previous operation as its
//  source.
//  For example:
//  List<T> aList;
//      aList.filter( predicate ).reverse().randomise().count();
//      aList.reverse().fiter( predicae ).slice( Range ).forEach( doSomething );
//
//  Terminal oprations do not return a List<T> and consequently are always the
//  final operation on a list
//  List<T> aList;
//      aList.count();
//      aList.add( T element );
//

#ifndef List_hpp
#define List_hpp

#include <stdio.h>
#include <vector>
#include <algorithm>
#include <random>
#include <stack>
#include "Range.hpp"
#include "RandomGenerator.hpp"

// forward declaration
class Person;

template<class T> class List
{
private:
    int cursor = 0;
    static const int notFound = -1;
    std::vector<T> theElements;

public:
    List<T>()
    {
        cursor = 0;
    }
    
    ~List()
    {
        // do nothing, it is up to the client to handle deletion and cleanup of elements
    }
    
    // reset iteration cursor to position (default is zero)
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    void resetCursor( int position = 0 )
    {
        cursor = position;
    }
    
    // returns true if not at the end of the list
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    bool hasNext()
    {
        return cursor < theElements.size();
    }
    
    // returns the element at the current cursor position and increments the cursor
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    T next()
    {
        return theElements[ cursor++ ];
    }
    
    // create a list containing a contiguous part of the current list
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> slice( int start, int end )
    {
        assert( start >= 0 && start < end && end < theElements.size() );

        Range range( start, end );
        
        return slice( range );
    }
    
    // create a list containing a contiguous part of the current list
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> slice( Range range )
    {
        assert( range.begin() >= 0 && range.begin()  < range.end() && range.end() < theElements.size() );

        List<T> listSlice;
        
        while ( range.hasNext() )
        {
            listSlice.add( theElements[ range.next() ] );
        }
        
        return listSlice;
    }
    
    // adds another list to this list
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> add( List<T> toAdd )
    {
        for ( int index = 0; index < toAdd.count(); index++ )
        {
            add( toAdd[ index ] );
        }
        
        return *this;
    }
    
    // returna a copy of the list
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> copy()
    {
        List<T> newList;
        for ( int index = 0; index < theElements.size(); index++ )
        {
            newList.add( theElements[ index ] );
        }

        return newList;
    }
    
    // assignment operator
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> operator=( List<T> rhs )
    {
        List<T> copy;
        
        for ( int item = 0; item < rhs.count(); item++ )
        {
            copy.add( rhs[ item ] );
        }
        
        return copy;
    }
    
    // returns a copy of the list with all elements in reverse order
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> reverseCopy()
    {
        return copy().reverse();
    }
    
    // returns a copy of the list with all elements in random order
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> randomisedCopy()
    {
        return copy().randomise();
    }
      
    // returns a list containing only those items that satisfy the predicate
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> filter( bool ( predicate( T ) ) )
    {
        List<T> filteredList;
        
        for ( int item = 0; item < theElements.size(); item++ )
        {
            if ( predicate( theElements[ item ] ) )
            {
                filteredList.add( theElements[ item ] );
            }
        }
        
        return filteredList;
    }
    
    // randomly shuffle the list
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> shuffle()
    {
        std::shuffle( theElements.begin(), theElements.end(), std::default_random_engine( rand() ) );
        cursor = 0;
        return *this;
    }
    
    // reverse the list
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> reverse()
    {
        std::reverse( theElements.begin(), theElements.end() );
        cursor = 0;
        return *this;
    }
    
    // get an element from indexed position
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    T get( int index )
    {
        assert( index < theElements.size() );
        return theElements[ index ];
    }
    
    // gets a number of elements randomly from the list, does not change the cursor
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> randomGet( int howMany )
    {
        List<T> randomList;
        
        // only get as many as we can, some lists are small slices
        if ( howMany > count() )
        {
            howMany = count();
        }

        for ( int index = 0; index < howMany; index++ )
        {
            randomList.add( theElements[ RandomGenerator::getInstance().getRandomInt( count() ) ] );
        }
        
        return randomList;
    }
    
    // array indexing function
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    T operator[]( int index )
    {
        assert( index < theElements.size() );
        return theElements[ index ];
    }
    
    // return index of element in collection
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    int indexOf( T element )
    {
        for ( int index = 0; index < theElements.size(); index++ )
        {
            if ( theElements[ index ] == element )
            {
                return index;
            }
        }
        return notFound;
    }
    
    // insert element at end of list, return position of element
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    int add( T element )
    {
        theElements.push_back( element );
        
        return static_cast<int>( theElements.size() );
    }
    
    // insert element at specified location
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    bool add( T element, int position )
    {
        if ( position >= 0 && position < theElements.size() )
        {
            theElements[ position ] = element;

            return true;
        }
        return false;
    }
 
    // removes element at specified postition (does NOT delete it)
    // returns TRUE if successful
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    bool remove( int position )
    {
        assert( position < theElements.size() );
        
        bool removed = false;
        if ( position >= 0 && position < theElements.size() )
        {
            theElements.erase( theElements.begin() + position );

            removed = true;
        }
        cursor = 0;
        return removed;
    }
    
    // returns TRUE if element contained in collection
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    bool contains( T element )
    {
        for ( int index = 0; index < theElements.size(); index++ )
        {
            if ( theElements[ index] == element )
            {
                return true;
            }
        }
        
        return false;
     }
    
    // removes all elements from collection
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    void clear()
    {
        theElements.clear();

        assert( theElements.size() == 0 );
        cursor = 0;
    }
    
    // returns TRUE if collection is emply
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    bool isEmpty()
    {
        return theElements.size() == 0;
    }
    
    // return the current value of cursor without advancing, enables a client
    // to obtain multiple copies of the same element, useful if after reading
    // the current element you need another function to take over processing
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    int current()
    {
        return cursor;
    }
    
    // return the first element in the list
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    T begin()
    {
        return theElements[ 0 ];
    }
    
    // return the last element in the list
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    T end()
    {
        return theElements[ static_cast<int>( theElements.size() ) ];
    }
    
    // sort the elements based upon the condition - the condition is a binary
    // predicate that returns true if lhs element is smaller that rhs element
    // this is a cumulative operation, it can be the source of another non-terminal operation
    List<T> sort( bool( condition( T, T ) ) )
    {
        std::sort( theElements.begin(), theElements.end(), condition );
        return *this;
    }
    
    // return the number of elements that satisfy the predicate
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    int countIf( bool ( predicate( T ) ) )
    {
        int retVal = 0;
        
        for ( int item = 0; item < theElements.size(); item++ )
        {
            if ( predicate( theElements[ item ] ) )
            {
                ++retVal;
            }
        }
                
        return retVal;
    }
    
    // accumulate elements using the counter(T) function
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    int accumulate( int ( counter( T ) ) )
    {
        int retVal = 0;
        
        for ( int item = 0; item < theElements.size(); item++ )
        {
            retVal += counter( theElements[ item ] );
        }
        
        return retVal;
    }
    
    // apply function doSomething(T) to each element
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    void forEach( void doSomething( T ) )
    {
        for ( int item = 0; item < theElements.size(); item++ )
        {
            doSomething( theElements[ item ] );
        }
    }
       
    // return size of the list
    // this is a terminal operation, it cannot be used to 'feed' another List operation
    int count()
    {
        return static_cast<int>( theElements.size() );
    }
};

#endif /* List_hpp */
