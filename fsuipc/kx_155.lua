port_file = "kx155_port.txt"
speed = 9600
handshake = 0
port_number = 3
----End of Variables section -------------------------------------

-- split a string
function string:split(delimiter)
  local result = { }
  local from  = 1
  local delim_from, delim_to = string.find( self, delimiter, from  )
  while delim_from do
    table.insert( result, string.sub( self, from , delim_from-1 ) )
    from  = delim_to + 1
    delim_from, delim_to = string.find( self, delimiter, from  )
  end
  table.insert( result, string.sub( self, from  ) )
  return result
end


function find_kx155()
  for port_number = 1,10 do
    com_port = com.open("COM"..port_number, speed, handshake)
    if com_port ~= 0 then
      ipc.display("Checking Com"..port_number.., 5)
      com.write(com_port, "ID\n")
      for sleep_count = 1,10 do
        ipc.sleep(0.1)
        data, _ = com.read(com_port, 100, 7)
        if (data) then
          if (data == "KX155:2") then
            ipc.display("Found KX155 on Com"..port_number, 5)
            return port_number, com_port
          end
          ipc.display("Bad ID on Com"..port_number..": "..data, 5)
          break
        end
      end
    else
      ipc.display("Nothing plugged into Com"..port_number, 5)
    end
  end
  ipc.display("Failed to find KX155", 5)
  return 0, nil
end

function str_to_bcd(str)
  num = 0
  length = string.len(str)
  for i = length, 1, -1  do
    digit = string.byte(str, i) - 0x30
    num = logic.Or(num, logic.Shl(digit, (length - i) * 4))
  end
  return num
end


display_offsets = {
  0x3118, -- Com2 Active
  0x311C, -- Com2 Standby
  0x0352, -- Nav2 Active
  0x3120  -- Nav2 Standby
}
function exec_cmd(command)
  index_str, frequency = string.match(command, "FREQUENCY:(%d):(%d%d%d%d)")
  index = tonumber(index_str)
  if (index and index <= 4) then
    ipc.writeUW(display_offsets[index], str_to_bcd(frequency))
  end

  nav_ident = string.match(command, "NAV_ID:(%d)")
  if (nav_ident) then
    ipc.writeLvar("L:Nav2PullIdent", tonumber(nav_ident))
  end

  com_25k = string.match(command, "COM_50K_STEP:(%d)")
  if (com_25k) then
    ipc.writeLvar("L:Com2InnerKnobPull", tonumber(com_25k))
  end

  power_on = string.match(command, "POWER_ON:(%d)")
  if (power_on) then
    ipc.writeLvar("L:Com2OnOff", tonumber(power_on))
  end
end

function init_kx155(com_port)
  event.com(com_port, 50,1, "SerialRx")
  com.write(com_port, "INIT\n")
  for index = 1,4 do
    bcd_freq = ipc.readUW(display_offsets[index])
    com.write(com_port, string.format("%d:%04X\n", index, bcd_freq))
  end
end

function SerialRx(com_port, datastring, length)
  for _, command in ipairs(datastring:split("\n")) do
    exec_cmd(command)
  end
end

do
  _, com_port = find_kx155()
  ipc.sleep(10)
while (com_port != nil)
init_kx155(com_port)

--function get_frequencies(time)
--  com2_active = string.format("%04X", ipc.readUW(0x3118))
--  ipc.log("Com 2 Active " .. com2_active)
--end

--event.timer(1000, "get_frequencies")
