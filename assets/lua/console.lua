writeln(ID, "Hi you hateful motherfucker, let's kill someone!")
local cheats = 0
while true do --Główna pętla
    local a = read(ID)
    --Ogólnodostępne
    if string.find(a, "cheats.set ") then --Dostęp do cheatów
        a = string.gsub(a, "cheats.set ", "")
        if tonumber(a) == 0 then
            cheats = 0
            writeln(ID, "Nah, ok. No cheats.")
        elseif tonumber(a) == 1 then
            cheats = 1
            writeln(ID, "Who is useless cheater? Yes, you!")
        end

    elseif tostring(a) == "help" then --Pomoc
        write(ID, "=======standard=======")
        write(ID, "cheats <0|1> - (dis/en)ables you to use cheats")
        write(ID, "help - displays some helpful info")
        write(ID, "========cheats========")
        write(ID, "hp.set <n> - sets your hp to 'n'")
        writeln(ID, "shield.set <n> - sets your shield points to 'n'")

    elseif tonumber(cheats) == 1 then --Cheaty
        if string.find(a, "shield.set ") then --Tarcza
            a = string.gsub(a, "shield.set ", "")
            if tonumber(a) < -1 or tonumber(a) > SHgetMax() then
                writeln(ID, "Your shield points must fit between -1 and " .. SHgetMax(), STATE_ERR)
            else
                writeln(ID, "Shield set to " .. a)
                SHset(tonumber(a))
            end

        elseif string.find(a, "hp.set ") then --Punkty życia
            a = string.gsub(a, "hp.set ", "")
            if tonumber(a) < -1 or tonumber(a) > HPgetMax() then
                writeln(ID, "Your health points must fit between 0 and " .. HPgetMax(), STATE_ERR)
            else
                writeln(ID, "HP set to " .. a)
                HPset(tonumber(a))
            end

        else --Ups?
            writeln(ID, "Clarify, idiot. (type \"help\" for some help)", STATE_ERR)
        end

    else --Ups?
        writeln(ID, "Clarify, idiot. (type \"help\" for some help)", STATE_ERR)
    end
end
