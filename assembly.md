# cforce build process

(imp: consider redoing arm w/ new wood (paint or varnish to reduce effects of moisture); only precise positioning is matching shaft plates (.005 clearance--drill bolt holes for arm in clamped-down arm on drill press, check w/square, use plate as template; shaft hole is 1+1/4 in))

## while flat
### frame
- test both sides of frame w/bearing blocks
- put on top gussets (should still have, A motor & B encoder) and aluminum plates on outsides
- put on bearing blocks, make sure hole registration (for bearing blocks, shaft, outrigger bolts) is correct on both sides of frame, then attach gussets with plenty of fasteners.
- remove broken-off screws in holes however necessary

(imp: plate/threaded rod/plate for interior braces instead of screws, esp in center)

(imp: aluminum plate on motor side inside, will guard bearing block holes)

### meanwhile, electronics
- test arm pneumatics (arduino pin 5, use blink; leak test in extended and retracted positions; tape on encoder & test launch signal with real code and manual spin)
- check wifi credentials: pull wifly & attach to usb plug, connect (ttyusb0 or usbserial, check dmesg) using picocom (baud rate in code comments)--check command ref for rn171 wifly
- check # acrylic rings (make extras for backup)
- acrylic plate fits a 3s 2200mah lipo battery, the same that is used for Icarus' remote.

## standing up
### assemble frame
- check squareness of motor tower (on level floor)
- stack frame halves and align bottoms to check alignment of bearing blocks/shaft (shim, recut or unscrew gussets and adjust as necessary)
- attach motor side A-frame to motor tower (need to find cross-brace and second base gusset for frame and spacer for tower, there are a total of 4 points of attachment between motor tower and frame)
- screw scrap wood brace into center of stood-up frame
- stand up other frame, position all bottom interior braces (measure inside distance), screw in temp brace
- put bearing blocks on shaft and test in frame for level and perpendicular to motor side frame (remove when done)
- screw in bibs (3in screws)
### install arm
- sand down indents and rust on shaft, load bb, 2 acrylic rings, 2 collars, put bolts in inward from motor side (washers both sides, careful not to block encoder holes), put on nuts but don't tighten
- slide arm against frame (electronics away from motor), load 2 collars (hex key collar near arm), 2 acrylic rings, bearing block
- work shaft through toward encoder side frame (pound w/rubber mallet, support w/ lift/pull from bottom of arm as necessary) until frame side bb/rings/collar just barely leaves room for encoder hole
- bolt in bearing blocks
- position arm, insert shaft key, remove temp brace, verify squareness, snug shaft collars and hand-spin through single rotation (checking squareness and clearance), tighten shaft collars
### finish frame
- attach outriggers, noting that the 2x4 that runs along the ground parallel to the arm rotation axis must be attached first to the 2x12, THEN the 2x12 bolted to the inner frame
- attach side supports, make sure motor tower is well-secured
- put in center decking

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

## power
### high-voltage  wiring
- Warning: VFD capacitors hold charge for several minutes after powerdown!
- Wired as per the manual for the vfd (Schnieder Electric ATV61HU55M3).
- Correct order for VFD-to-motor wiring noted in writing on power panel under where the VFD mounts.
- If the 3 phase conductors are wired incorrectly, the arm will spin backwards.

### launch preparation
- balance & spin tests
- charge pneumatics
- calibrate launch constants (equation in current software is releasetick = A * RPM + B)
- The wait in the SW for a newline before sending any additional data is intentional, if you send data to an unassociated wifly it will become unresponsive until power cycle.
- Arduino must be reset and launch parameters re-entered after each firing 
