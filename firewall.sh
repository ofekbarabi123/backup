#!/bin/bash

if [ "$#" -ne 1 ]; then
	exit
fi

while read -r line; do
	IFS=',' read -r -a arr <<< "$line"
	tmp=$(cat | grep -o '^[^#]*' | sort | uniq | ./firewall.exe "${arr[0]}" 2>/dev/null | ./firewall.exe "${arr[1]}" 2>/dev/null | ./firewall.exe "${arr[2]}" 2>/dev/null | ./firewall.exe "${arr[3]}" 2>/dev/null)
	echo "$tmp"
done < <(cat)

exit 0
