RSC Sundae 1.6.0
----------------

* protocol: Added support for mudclient201 and most 2002 clients.
* script: Made dialogue timeout in 20 seconds.
* karamjaship: Allow the Crandor option to eventually disappear.
* trade: Check if the receiving player's inventory will be full.
* server: Add variable deletion time for temporary objs (e.g.
  items lost on deathi disappear slower).
* admin: Add noclipping command (requires client support).

RSC Sundae 1.5.1
----------------

* configure: Initial support for System V/Solaris.
* player: Revised spell failure formula.
* server: Revised tick rate.
* metalwork: Fixed hatchet message.

RSC Sundae 1.5.0
----------------

* npc: Faster, more scientific walk timer.
* mining: Fix "nothing interesting happens" with "uninteresting" rocks.
* loop: Add support for select-based event loop.
* loop: Removed support for libev.
* protocol: Add libtommath-based RSA implementation as alternative to
  OpenSSL.
* script: Fix some Lua stack leaks.
* win32: Add support for Windows XP.

RSC Sundae 1.4.0
----------------

* server: Support .txt overrides for config.jag.
* server: Support local overrides for customized maps.
* player: Restrict melee NPC attack per AR "banker killing" bug fix.
* player: Drop all stackable items on death.
* script: Fix casting on multiple items of the same type.
* stat: Ranged levels should trigger a combat level update.
* kebab: Added 2 tick delay.
* admin: Added ::skull and ::empty commands.
* win32: Fix runtime segfault, remove libev dependency.

RSC Sundae 1.3.0
----------------

* dragon: Breathe fire when spells are used.
* magic: Use monster-specific missiles per bluerose's report.
* settings: Add an option instead of hardcoding config/maps revs.
* imp: Fixed chef's hat drop.
* protocol: Add support for client version 135 (used by Runebot).

RSC Sundae 1.2.0
----------------

* Rework the way retreating affects aggression...
* implement so-called "cast spell to get caught instantly" "bug"
* implement aggression==2 NPCs re-attacking players who retreat
* implement retreating gives a grace period from aggressive NPCs
* Implemented basic functionality for disk of returning.
* Implemented half full wine jug after finding footage.
* Implemented Doric anvil busy messasge after finding
  screenshot.
* Allow 100% successful casts with 32 magic bonus.
* Prevent players from getting themselves stuck by
  casting spells on Delrith.
* When no victor in player death, items are owned by self.
* Added missing chaos-rune drop to darkerwiz.
* Added "already made of gold" message to alchemy spells.
* Fixed selling gold amulets to Grum with the authentic
  messed up config
* Read item spawn stack sizes from loc direction chunk of landscape.
* Made holiday drops unowned.

RSC Sundae 1.1.3
----------------

* Stricter validation of ground item ownership to not
  have PID bugs.
* Cancel future ranged events when target is unreachable
  to prevent "I can't get a clear shot" message looping.
* Fixed Paralyze Monster freezing the combat round counter.
* Fixed Sir Vyvin getting stuck in a busy state.
* Fixed certain NPCs being stuck in busy state when menu
  times out during oploc.

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
