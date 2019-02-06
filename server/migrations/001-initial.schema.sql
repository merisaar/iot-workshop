CREATE TABLE Sensor (
    name TEXT PRIMARE KEY,
    firstonline TEXT NOT NULL,
    lastonline TEXT NOT NULL
);
CREATE TABLE Reading (
    id INTEGER PRIMARY KEY AUTOINCREMENT, 
    sensorname TEXT,
    temperature NUMERIC(10, 2),
    pressure  NUMEROC(10,2), 
    humidity  NUMEROC(10,2), 
    timestamp TEXT,
    FOREIGN KEY (sensorname) REFERENCES sensor(name)
);

-- Down
DROP TABLE Sensor;
DROP TABLE Reading;
    
)