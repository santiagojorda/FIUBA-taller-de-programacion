echo 'Player 1' >> __client_0_pipe__
echo 'Player 2' >> __client_1_pipe__
echo 'Player 3' >> __client_2_pipe__

echo 'Pickup 2' >> __client_0_pipe__
echo 'Pickup 3' >> __client_0_pipe__
echo 'Pickup 3' >> __client_0_pipe__
echo 'Pickup 1' >> __client_0_pipe__
echo 'Pickup 1' >> __client_0_pipe__
echo 'Pickup 2' >> __client_0_pipe__
echo 'Pickup 4' >> __client_0_pipe__
echo 'Pickup 4' >> __client_0_pipe__
echo 'Pickup 4' >> __client_0_pipe__


echo 'Read 3' >> __client_0_pipe__
echo 'Read 4' >> __client_1_pipe__
echo 'Read 6' >> __client_2_pipe__

# Agrego el sleep para asegurarme que el server envia las
# acciones de respawn.
sleep 5

echo 'Exit' >> __client_0_pipe__
echo 'Exit' >> __client_1_pipe__
echo 'Exit' >> __client_2_pipe__
