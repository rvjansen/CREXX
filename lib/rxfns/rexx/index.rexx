/*
 * crexx index
 * VM-TSO compatible implementation of pos()
 */

options levelb

index: procedure = .int
  arg expose haystack = .string, needle = .string, start = 1

return pos(needle,haystack,start)


pos: procedure = .int
  arg expose needle = .string, haystack = .string, start = 1

