# List
The list<T> class is a template to hold any type, from simple fundamental types to complex classes.  List has a rich interface which supports many
of the operations than one might want to perform on a collection. It has built-in iteration cpabilities, and has powerful filtering capabilities
by the use of predicate functions.  List supports two types of operation, final opperation (which I call terminal operations) and cumulative
operations that can be stacked or nested.
For example;
  Terminal operations such as count() and forEach( doSomething ) are always the final operations applied to a List:
    aSampleList.count() // this is a terminal operation that returns the size of the list
    
  Cumulative operations such as filter( predicate ) and slice( range ) return a copy of the list after applying the predicate:
    aSampleList.filter( predicate ).reverse() // this returns a shuffled copy of the sub-list returned by the filter predicate.
    
Please let me know of any isues that you find, and I'll do my best to fix them as soon as I can.

Remember: If you decide to use List, please retain the header that includes my copyright in all source code, and reference its inclusuion
in any release notes.
Thank you all

  
