Working solution for 2016 day 1 both parts

The first part was easy enough, the second part took a while to get
right, because my program kept failing to recognise when it had stepped
on a point it had already visited.  I thought there were 2 ways of
tracking steps:

  1: keep a list of coords where you step, adding more coords each step
     more space efficient, but takes longer to check for each step
     because you need to run through the whole list (I think)
  2: draw a map of where you step in a 2D matrix
     takes the most possible space in memory but checking whether you
     stepped somewhere is instant because you can look it up by coords
     in your grid

I picked the second one because it seemed faster and I wasn't in the
mood for linked lists or malloc resizing arrays.  During debugging this
I realised it would frequently step on already visited points and then
just carry on walking, something about the "already visited" condition
didn't work using a break statement, and also not in the while condition
wtf.  By magic, the thing that got it to work was to make move() return
a boolean and return early when you step on something AND check that
value in the measure function and return early from there too!  I'm not
sure why this worked, return should have done more-or-less the same as
break, but whatever.

I don't think this code is amazing, I used lots of globals cos I wasn't
in the mood to pass around variables to functions everywhere when all
we're really dealing with mainly is coords.
