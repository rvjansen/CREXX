options levelb comments_dash
namespace data_List expose ListIterator
import rxfnsb

/**
 * Iterator for the List class.
 *
 * Supports forward traversal of a List.
 *
 * Typical usage:
 *
 *   it = list.iterator()
 *   do while it.hasNext()
 *     say it.next()
 *   end
 */
ListIterator: class
val   = .stem
index_  = .int

/**
 * Factory method.
 *
 * @param list  The List to iterate over.
 */
  *: factory
    arg s= .stem
    val	= s
    index_= 1
    return
    
    /**
    * Returns 1 if more elements are available.
    *
    * @return 1 if there is a next element, 0 otherwise.
    */
  hasNext: method = .int
    say 'in hasNext()'
    say val.size()
    say index_
    say 'end hasNext()'
    if val.size() >= index_ then return 1
    return 0
    
    
    /**
    * Returns the next element in the iteration.
    *
    * Advances the cursor.
    *
    * @return The next element, or 0 if none available.
    */
  next: method = .string
    -- if i >= val.size() then
    --   return 0  -- TODO exception
    
    index_ = index_ + 1
    say 'in next'
    say  index_
    k = val.key(index_)
    say '>>k'
    say k
    v = val.value(k)
    say '>>v'
    say v
    say 'end next'
    return v
    
    /**
    * Returns the current i (1-based).
    *
    * @return Current position in the list.
    */
  index: method = .int
    return index_
    
    
    /**
    * Resets the iterator to the start.
    */
  reset: method = .void
    index_ = 0
    return
