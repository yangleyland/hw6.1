#!/bin/bash
#init wd is ~workspace

STARTER_FILES_DIR="hw6"

# clone student repo and checkout specified commit
cd $STARTER_FILES_DIR
REPO_URL=$(git remote get-url origin)
echo REPO_URL: $REPO_URL

#check for https url
if [[ "$REPO_URL" == *"https"* ]]; then
  echo "https URL found. Make sure remote git origin URL is ssh!"
  exit 1
fi

#does the SSH url end in .git?

if [[ "${REPO_URL: -4}" != ".git" ]]; then
  REPO_URL=$REPO_URL.git
fi

IFS='.''/' read -ra REPO_NAME_ARR <<< "$REPO_URL"
REPO_NAME=${REPO_NAME_ARR[-2]}
echo REPO_NAME: $REPO_NAME

cd ../.guides
#pwd
#ls
rm -rf $REPO_NAME #delete old copy of repo if it exists
#ls
git clone --quiet $REPO_URL 2> /dev/null
#ls

if [[ ! -d $REPO_NAME ]] ;
then
echo "Unable to checkout your repo. Please verify that you have performed the steps on this page correctly and try again."
exit 1
fi
#ls
cd $REPO_NAME

for F in boggle.cpp boggle-driver.cpp boggle.h dict.txt hash-check.cpp hash.h ht.h ht-test.cpp Makefile str-hash-test.cpp .gitignore
do

  if [[ ! -f $F ]] ;
  then
    echo "$F is not found in the repo. Did you 'git add $F' and 'git commit' and 'git push'?"
  else
    echo "$F has been checked in properly"
  fi
done
