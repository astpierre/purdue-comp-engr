#!/usr/bin/env bash

set -o errexit
set -o errtrace
set -o nounset
set -o pipefail
printf 'gitScript beginning...\n'
cd ~/ECE264
git remote rm origin
git remote add origin git@github.com:astpierre/ECE264.git
printf 'Removed, re-added remote origin.\n'
ssh-keygen -t rsa -b 4096 -C "web@github.com"
mv id_rsa ../.ssh
mv id_rsa.pub ../.ssh
printf 'Generated new key.\n'
eval "$(ssh-agent -s)"
ssh-add ~/.ssh/id_rsa
printf 'Add the key below to your SSH deploy keys on GitHub.com\n'
cat ~/.ssh/id_rsa.pub
git remote add origin git@github.com:astpierre/ECE264.git
git remote -v
