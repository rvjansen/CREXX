/* rexx linesize bif */
options levelb
/*
 * here mainly because it needs a native implementation on z/VM
 * and probably other OS; this one returns 999999999 to be consistent
 * with the Rexx compiler for zSeries 
 */  

linesize: procedure = .int
  arg expose string1 = .string
  result = 999999999
  return result
