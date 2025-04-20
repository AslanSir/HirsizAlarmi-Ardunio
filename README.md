# HirsizAlarmi-Ardunio

## Çalışma Mantığı

- Yeşil butona 3 saniye basılı tutunca bir uzaklığı hafızasına kaydeder. Ardından sürekli ölçüm yapar. Eğer herhangi bir anda, ölçtüğü uzaklık ile hafızasına kaydettiği uzaklık arasında sapma değerinden büyük bir fark oluşursa alet ötmeye başlar. Kırmızı butona basınca sistem devre dışı kalır.

- **Çalışıyorsa** LED sürekli yanar, **çalışmıyorsa** LED sönük kalır.

- İlk ölçümde eğer ölçüm yapamazsa veya girilen minimum ile maximum değerler dışında bil ölçüm yaparsa buzzer 3 kere ses çıkarır ve sonucunda LED söner. Sistem bu haliyle devre dışı şekilde kalır.
