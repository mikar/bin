#!/usr/bin/env bash
country='US'
echo "Your usual country? [Y/n]"
read answer
case $answer in
    ""|[Yy]|[Yy][Ee][Ss]) echo "Using default country"
        sudo reflector --verbose --country=$country -l 20 -p http --sort rate --save /etc/pacman.d/mirrorlist
        ;;
    [Nn]|[Nn][Oo]) reflector --list-countries | sed 's/[0-9]//g'
        echo -e  "\nWhat is the two digit country code of your current country?"
        printf "    Country code: "
        read country
        country="${country^^}"
        sudo reflector --verbose --country=$country -l 20 -p http --sort rate --save /etc/pacman.d/mirrorlist
        echo "Would you like to make this your default country? [y/N]"
        read answer
        case $answer in
            [Yy]|[Yy][Ee][Ss]) sed -i "2s/country='[A-Z][A-Z]'/country='$country'/" $0
               ;;
        esac
        ;;
esac

