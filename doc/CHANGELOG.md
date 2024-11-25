RSC Sundae 1.1.3
----------------

* Stricter validation of ground item ownership to not
  have PID bugs.
* Cancel future ranged events when target is unreachable
  to prevent "I can't get a clear shot" message looping.
* Fixed Paralyze Monster freezing the combat round counter.
* Fixed Sir Vyvin getting stuck in a busy state.

RSC Sundae 1.1.2
----------------

* Fixed play_time recording for proper functioning of ::time.
* Fixed "should be able to cut web with battle axe".
* Fixed "duplicate ground items not visibly removed".
* Fixed wizard's mind bomb.
* Fixed Straven not giving a spare key in Shield of Arrav.
* Added missing gypsy dialogue.
* Remove players from zone on logout.
* Eliminate compiler warnings in ::onlinelist implementation.
* Various fixes for subtle combat bugs.

RSC Sundae 1.1.1
----------------

* Added ::saveall admin command to save all players to the
  database (useful before shutdown).
* Implemented silk selling restriction in Al Kharid general store.
* Disallow equipping items during active player scripts (thanks Logg).
* Imps drop flourpot, not flourheap (thanks Logg).
* Tighter distance limit on nearvisnpc.

RSC Sundae 1.1.0
----------------

* Added manual page and installation targets
* Adjustments to NPC aggression and following
* Removed potentially bug-causing teleportation code
* Fixed monsters dropping phoenix crossbows
* Fixed the dreaded combat assertion

RSC Sundae 1.0.0
----------------

* First stable release
