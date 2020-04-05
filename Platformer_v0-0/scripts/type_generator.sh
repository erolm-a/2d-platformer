#!/bin/bash

# this script is expected to have the $GAME_SRC_DIRECTORY
# variable set


include_file="$GAME_SRC_DIRECTORY/game/game_types.h"
mapper="$GAME_SRC_DIRECTORY/game/game_types.cpp"

echo "/* Generated by script/type_generator.sh */" > $mapper
echo "/* Generated by script/type_generator.sh */" > $include_file

echo '#include <unordered_map>
#include "game_types.h"

std::unordered_map<string, game_instance_generic*> _association {' >> $include_file

is_first="1"
for i in $(egrep --color=never "^EXPORT_GAME_CLASS" \
            $(find $GAME_SRC_DIRECTORY -name "*.h" \
                -and -not -name "game_instance_generic.h"))
do
    classname=$(echo $i | sed -E 's/.*\(([^)]+)\).*/\1/')
    filename=$(echo $i | cut -d ':' -f 1 | sed -E 's/.*\/game\///')

    echo '#include "$filename"' >> $include_file
    if [[ $is_first -eq "0" ]]; then
        echo ', {"$classname", ($classname*) nullptr}' >> $mapper
    else echo '{"$classname", ($classname*) nullptr}' >> $mapper
        is_first=0
    fi
done

echo "};" >> $mapper
