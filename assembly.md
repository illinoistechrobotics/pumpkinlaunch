# cforce build process

(imp: consider redoing arm w/ new wood (paint or varnish to reduce effects of moisture); only precise positioning is matching shaft plates (.005 clearance--drill bolt holes for arm in clamped-down arm on drill press, check w/square, use plate as template; shaft hole is 1+1/4 in))

## while flat
### frame
- test both sides of frame w/bearing blocks
- put on top gussets (should still have, A motor & B encoder) and aluminum plates on outsides
- put on bearing blocks, make sure hole registration (for bearing blocks, shaft, outrigger bolts) is correct on both sides of frame
- remove broken-off screws in holes however necessary

(imp: plate/threaded rod/plate for interior braces instead of screws, esp in center)

(imp: aluminum plate on motor side inside, will guard bearing block holes)

### meanwhile, electronics
- test arm pneumatics (arduino pin 5, use blink; leak test in extended and retracted positions; tape on encoder & test launch signal with real code and manual spin)
- check wifi credentials: pull wifly & attach to usb plug, connect (ttyusb0 or usbserial, check dmesg) using picocom (baud rate in code comments)--check command ref for rn171 wifly
- check # acrylic rings (make extras for backup)

## standing up
### assemble frame
- check squareness of motor tower (on level floor)
- stack frame halves and align bottoms to check alignment of bearing blocks/shaft (shim or recut as necessary)
- attach motor side A-frame to motor tower (need to find cross-brace and second base gusset for frame and spacer for tower)
- screw scrap wood brace into center of stood-up frame
- stand up other frame, position all bottom interior braces (measure inside distance), screw in temp brace
- put bearing blocks on shaft and test in frame for level (remove when done)
- screw in bibs (3in screws)
### install arm
- sand down shaft, load bb, 2 acrylic rings, 2 collars, put bolts in inward from motor side (washers both sides, careful not to block encoder holes), put on nuts but don't tighten
- slide arm against frame (electronics away from motor), load 2 collars (hex key collar near arm), 2 acrylic rings, bearing block
- work shaft through toward encoder side frame (pound w/rubber mallet, support w/ lift/pull from bottom of arm as necessary) until frame side bb/rings/collar just barely leaves room for encoder hole
- bolt in bearing blocks
- position arm, insert shaft key, remove temp brace, verify squareness, snug shaft collars and hand-spin through single rotation (checking squareness and clearance), tighten shaft collars
### finish frame
- put in center decking
- attach outriggers and side supports, make sure motor tower is well-secured

(imp: use single large bolt between top of motor tower and a-frame instead of screw)

- shaft collar on outside of motor frame, sprocket on, align sprocket w/ motor (easier w/ rain cover off), tighten shaft collar, put in key, make sure motor bolts are loose, chain on, add/remove washers under motor flange as necessary to adjust chain tension (1/4 to 1/2 inch of hand chain deflection & good sound during rotation), tighten sprocket set screws
### finish electronics
- mount large encoder bracket

(imp: change from holes to slots in encoder mount)

- bolt encoder to acrylic panel (m3x10?)
- bolt back of acrylic box to threaded end of shaft, w/ spacers so that a) bolt goes 7/8 in into end of shaft & b) end of box is just short of against arm of mounting bracket

(imp: carve space for bolt heads)

- assemble acrylic box around encoder, fishing wire (rj11 telephone cable) through side hole, & wrap in electrical tape
- fish through shaft (out to in is easiest)
- fish cable through hole in tupperware & secure (solder + heatshrink)

## with power
- do high-power wiring
- balance & spin tests
- calibrate launch constants

## before launch day
- get own outdoor ip camera for overnight monitoring
