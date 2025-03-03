/*
 *.  ReRadix
 *   Converts Arg(1) from radix Arg(2) to radix Arg(3) 
 *   Radix range is 2-16.  Conversion is via decimal
 *   After Brian Marks' version 
 */ 
options levelb

reradix: procedure = .string
arg subject = .string, FromRadix = .int, ToRadix = .int

subject = upper(subject)
 integer=0
 do j=1 to length(subject)
   /* Individual digits have already been checked for range. */
   integer=integer*FromRadix+pos(substr(subject,j,1),'0123456789ABCDEF')-1
   /* This test not for standard. */
    if pos('E',integer)>0 then do
      say "ReRadix unable"
      return ? 
    end
 end
 r=''
 if integer=0 then r='0'
 do while integer>0
    r=substr('0123456789ABCDEF',1+integer//ToRadix,1)||r
   integer=integer%ToRadix
 end
 /* When between 2 and 16, there is no zero suppression. */
 if FromRadix=2 & ToRadix=16 then
   r=right(r,(length(subject)+3)%4,'0')
 else if FromRadix=16 & ToRadix=2 then
   r=right(r,length(subject)*4,'0')
 return r

/* Length() Procedure */
length: procedure = .int
  arg string1 = .string

/* Substr() Procedure */
substr: procedure = .string
  arg string1 = .string, start = .int, len = length(string1) + 1 - start, pad = ' '

/* function prototype */
right: procedure = .string
arg string1 = .string, length = .int, pad = ' '

 /* function prototype */
pos: procedure = .int
arg string1 = .string, string2 = .string, start = 1

/* upper()  */
upper: procedure = .string
  arg expose string1 = .string
