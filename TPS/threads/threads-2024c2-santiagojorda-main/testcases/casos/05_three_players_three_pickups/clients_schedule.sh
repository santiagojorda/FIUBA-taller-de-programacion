echo 'Player 1' >> __client_0_pipe__
echo 'Player 2' >> __client_1_pipe__
echo 'Player 3' >> __client_2_pipe__


echo 'Pickup 1' >> __client_0_pipe__
# Para asegurar que el orden de los pickups sea tal como esta escrito
sleep 0.5
echo 'Pickup 2' >> __client_1_pipe__
# No debería poder levantar la caja ya que la levantó previamente
echo 'Pickup 2' >> __client_1_pipe__


echo 'Read 4' >> __client_1_pipe__
echo 'Read 3' >> __client_2_pipe__

# Agrego el sleep para asegurarme que el server envia los
# respawns de las cajas.
sleep 4

echo 'Exit' >> __client_0_pipe__
echo 'Exit' >> __client_1_pipe__
echo 'Exit' >> __client_2_pipe__
