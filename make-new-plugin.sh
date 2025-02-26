#! /bin/bash

# This script refactors this plugin into a new plugin with a name of your choice.
# To rename the plugin to "catsarebest", run `bash make-new-plugin.sh catsarebest`.

newname=openobserver
Newname=OpenObserver
NEWNAME=OPENOBSERVER

grep -rl openobserver . | grep -v .git | while read name; do
  sed -e "s+openobserver+$newname+g" -i.sedbackup "$name";
done

grep -rl OpenObserver . | grep -v .git | while read name; do  
  sed -e "s+OpenObserver+$Newname+g" -i.sedbackup "$name";
done 

grep -rl OPENOBSERVER . | grep -v .git | while read name; do  
  sed -e "s+OPENOBSERVER+$NEWNAME+g" -i.sedbackup "$name";
done 

find . -name "*openobserver*" | grep -v .git | while read name; do
  mv "$name" "$(echo "$name" | sed -e "s+openobserver+$newname+g")"
done

find . -name "*OpenObserver*" | grep -v .git | while read name; do
  mv "$name" "$(echo "$name" | sed -e "s+OpenObserver+$Newname+g")"
done
