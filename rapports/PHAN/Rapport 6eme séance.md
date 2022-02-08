Phan Damien

# Compte rendu séance 6

## Obtention de nouvelles données 

Grâce au code de l'exemple de la bibliothèque de MP6050_DMP6, on obtient des données en fonction de l'inclinaison du module GY-521.

```php

    #ifdef OUTPUT_READABLE_YAWPITCHROLL
        // display Euler angles in degrees
        mpu.dmpGetQuaternion(&q, fifoBuffer);
        mpu.dmpGetGravity(&gravity, &q);
        mpu.dmpGetYawPitchRoll(ypr, &q, &gravity);
        Serial.print("ypr\t");
        Serial.print(ypr[0] * 180/M_PI);
        Serial.print("\t");
        Serial.print(ypr[1] * 180/M_PI);
        Serial.print("\t");
        Serial.println(ypr[2] * 180/M_PI);
    #endif

```


