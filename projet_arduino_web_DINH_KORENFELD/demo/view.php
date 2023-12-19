<!DOCTYPE html>
<html lang="fr">

<head>
  <meta charset="utf-8">
  <meta content="width=device-width, initial-scale=1.0" name="viewport">

  <title>MediConnect </title>
  <meta content="" name="description">
  <meta content="" name="keywords">

  <!-- Favicons -->
  <link href="assets/img/arduino.png" rel="icon">

  <!-- Google Fonts -->
  <link href="https://fonts.googleapis.com/css?family=Open+Sans:300,300i,400,400i,600,600i,700,700i|Roboto:300,300i,400,400i,500,500i,600,600i,700,700i|Poppins:300,300i,400,400i,500,500i,600,600i,700,700i" rel="stylesheet">

  <!-- Vendor CSS Files -->
  <link href="assets/vendor/fontawesome-free/css/all.min.css" rel="stylesheet">
  <link href="assets/vendor/animate.css/animate.min.css" rel="stylesheet">
  <link href="assets/vendor/aos/aos.css" rel="stylesheet">
  <link href="assets/vendor/bootstrap/css/bootstrap.min.css" rel="stylesheet">
  <link href="assets/vendor/bootstrap-icons/bootstrap-icons.css" rel="stylesheet">
  <link href="assets/vendor/boxicons/css/boxicons.min.css" rel="stylesheet">
  <link href="assets/vendor/glightbox/css/glightbox.min.css" rel="stylesheet">
  <link href="assets/vendor/swiper/swiper-bundle.min.css" rel="stylesheet">

  <!-- Template Main CSS File -->
  <link href="assets/css/style.css" rel="stylesheet">
</head>

<body>

  <?php
  //Connect to database and create table
  $servername = "localhost";
  $username = "root";
  $password = "";
  $dbname = "demo";

  // Create connection
  $conn = new mysqli($servername, $username, $password, $dbname);
  // Check connection
  if ($conn->connect_error) {
    die("Database Connection failed: " . $conn->connect_error);
    echo "<a href='install.php'>If first time running click here to install database</a>";
  }
  ?>

  <!-- ======= Top Bar ======= -->
  <div id="topbar" class="d-flex align-items-center fixed-top">
    <div class="container d-flex align-items-center justify-content-center justify-content-md-between">
      <div class="align-items-center d-none d-md-flex">
        Dispositifs embarqués pour la santé
      </div>
      <div class="d-flex align-items-center">
        Système de Surveillance Médicale à Distance avec Arduino et IoT
      </div>
    </div>
  </div>

  <!-- ======= Header ======= -->
  <header id="header" class="fixed-top">
    <div class="container d-flex align-items-center">

      <a href="" class="logo me-auto">MediConnect</a>

      <nav id="navbar" class="navbar order-last order-lg-0">
        <ul>
          <li><a class="nav-link scrollto " href="#hero">Accueil</a></li>
          <li><a class="nav-link scrollto" href="#mesure">Mesure</a></li>
          <li><a class="nav-link scrollto" href="#contact">Contact</a></li>
        </ul>
        <i class="bi bi-list mobile-nav-toggle"></i>
      </nav><!-- .navbar -->


    </div>
  </header><!-- End Header -->


  <!-- ======= Hero Section ======= -->
  <section id="hero">
    <div id="heroCarousel" data-bs-interval="5000" class="carousel slide carousel-fade" data-bs-ride="carousel">

      <ol class="carousel-indicators" id="hero-carousel-indicators"></ol>

      <div class="carousel-inner" role="listbox">

        <!-- Slide 1 -->
        <div class="carousel-item active" style="background-image: url(assets/img/slide/slide-1.jpg)">
          <div class="container">
            <h2>Bienvenue à <span>MediConnect</span></h2>
            <p>Découvrez notre Système de Surveillance Médicale à Distance avec Arduino et IoT, redéfinissant l'avenir de la médecine.
              <br>
              Capteurs avancés, transmission en temps réel via le WiFi, interface intuitive : suivez les signes vitaux des patients à distance.
              <br>
              Explorez dès maintenant le futur de la médecine proactive.
            </p>
          </div>
        </div>

        <!-- Slide 2 -->
        <div class="carousel-item" style="background-image: url(assets/img/slide/slide-2.jpg)">
          <div class="container">
            <h2>Bienvenue à <span>MediConnect</span></h2>
            <p>Découvrez notre Système de Surveillance Médicale à Distance avec Arduino et IoT, redéfinissant l'avenir de la médecine.
              <br>
              Capteurs avancés, transmission en temps réel via le WiFi, interface intuitive : suivez les signes vitaux des patients à distance.
              <br>
              Explorez dès maintenant le futur de la médecine proactive.
            </p>
          </div>
        </div>

        <!-- Slide 3 -->
        <div class="carousel-item" style="background-image: url(assets/img/slide/slide-3.jpg)">
          <div class="container">
            <h2>Bienvenue à <span>MediConnect</span></h2>
            <p>Découvrez notre Système de Surveillance Médicale à Distance avec Arduino et IoT, redéfinissant l'avenir de la médecine.
              <br>
              Capteurs avancés, transmission en temps réel via le WiFi, interface intuitive : suivez les signes vitaux des patients à distance.
              <br>
              Explorez dès maintenant le futur de la médecine proactive.
            </p>
          </div>
        </div>

      </div>

      <a class="carousel-control-prev" href="#heroCarousel" role="button" data-bs-slide="prev">
        <span class="carousel-control-prev-icon bi bi-chevron-left" aria-hidden="true"></span>
      </a>

      <a class="carousel-control-next" href="#heroCarousel" role="button" data-bs-slide="next">
        <span class="carousel-control-next-icon bi bi-chevron-right" aria-hidden="true"></span>
      </a>

    </div>
  </section><!-- End Hero -->

  <main id="main">

    <!-- ======= Mesure Section ======= -->
    <?php
    $sql = "SELECT * FROM logs ORDER BY id DESC LIMIT 1";
    if ($result = mysqli_query($conn, $sql)) {
      // Fetch one and one row
      echo '<section id="mesure" class="pricing featured-services">';
      echo '<div class="container" data-aos="fade-up">';
      echo '<div class="section-title">';
      echo '<h2>Mesure</h2>';
      echo '</div>';
      echo '<div class="row">';

      while ($row = mysqli_fetch_row($result)) {
        // Température
        echo '<div class="col-lg-6 col-md-12 mt-4 mt-md-0 mb-4">';
        echo '<div class="box featured icon-box-pricing" data-aos="fade-up" data-aos-delay="200">';
        echo '<h3>Température <i class="fas fa-temperature-quarter" style="font-size: 26px;"></i></h3>';
        echo '<h4>' . $row[1] . ' °C</h4>';
        echo '</div>';
        echo '</div>';

        // Humidité
        echo '<div class="col-lg-6 col-md-12 mt-4 mt-md-0 mb-4">';
        echo '<div class="box featured icon-box-pricing" data-aos="fade-up" data-aos-delay="200">';
        echo '<h3>Humidité <i class="fas fa-droplet" style="font-size: 26px;"></i></h3>';
        echo '<h4>' . $row[2] . ' %</h4>';
        echo '</div>';
        echo '</div>';

        // Présence
        echo '<div class="col-lg-6 col-md-12 mt-4 mt-md-0 mb-4">';
        echo '<div class="box featured icon-box-pricing" data-aos="fade-up" data-aos-delay="200">';
        echo '<h3>Présence <i class="fas fa-person-chalkboard" style="font-size: 26px;"></i></h3>';
        // echo '<h4>' . ($row[3] == 1 ? "Oui" : "Non") . '</h4>';
        echo '<h4>' . $row[3] . '</h4>';
        echo '</div>';
        echo '</div>';

        // Distance
        echo '<div class="col-lg-6 col-md-12 mt-4 mt-md-0 mb-4">';
        echo '<div class="box featured icon-box-pricing" data-aos="fade-up" data-aos-delay="200">';
        echo '<h3>Distance (par rapport au capteur / la porte) <i class="fas fa-ruler" style="font-size: 26px;"></i></h3>';
        echo '<h4>' . $row[4] . ' m</h4>';
        echo '</div>';
        echo '</div>';
      }

      // Free result set
      mysqli_free_result($result);
    }

    mysqli_close($conn);
    ?>

    <!-- End Mesure Section -->

    <!-- ======= Contact Section ======= -->
    <section id="contact" class="contact">
      <div class="container">

        <div class="section-title">
          <h2>Contact</h2>
        </div>

      </div>

      <div>
        <iframe style="border:0; width: 100%; height: 350px;" src="https://www.google.com/maps/embed?pb=!1m18!1m12!1m3!1d2629.3061671118858!2d2.370966576158591!3d48.77604490649828!2m3!1f0!2f0!3f0!3m2!1i1024!2i768!4f13.1!3m3!1m2!1s0x47e673f65b15877f%3A0x52448ae9a3224654!2s122%20Rue%20Paul%20Armangot%2C%2094400%20Vitry-sur-Seine!5e0!3m2!1sfr!2sfr!4v1701854794607!5m2!1sfr!2sfr" frameborder="0" allowfullscreen></iframe>
      </div>

      <div class="container">

        <div class="row mt-5">

          <div class="col-lg-6">

            <div class="row">
              <div class="col-md-12">
                <div class="info-box">
                  <i class="bx bx-map"></i>
                  <h3>Notre Adresse</h3>
                  <p>122 Rue Paul Armangot, 94400, Vitry-sur-Seine</p>
                </div>
              </div>
              <div class="col-md-6">
                <div class="info-box mt-4">
                  <i class="bx bx-envelope"></i>
                  <h3>Email </h3>
                  <p>thi-thu-hien.dinh@etu.u-pec.fr<br>laura.korenfeld@etu.u-pec.fr</p>
                </div>
              </div>
              <div class="col-md-6">
                <div class="info-box mt-4">
                  <i class="bx bx-phone-call"></i>
                  <h3>Téléphone</h3>
                  <p>+33 1 23 45 67 89<br>+33 1 23 45 67 89</p>
                </div>
              </div>
            </div>

          </div>

          <div class="col-lg-6">
            <form action="forms/contact.php" method="post" role="form" class="php-email-form">
              <div class="row">
                <div class="col-md-6 form-group">
                  <input type="text" name="name" class="form-control" id="name" placeholder="Votre Nom" required="">
                </div>
                <div class="col-md-6 form-group mt-3 mt-md-0">
                  <input type="email" class="form-control" name="email" id="email" placeholder="Votre Email" required="">
                </div>
              </div>
              <div class="form-group mt-3">
                <input type="text" class="form-control" name="subject" id="subject" placeholder="Sujet" required="">
              </div>
              <div class="form-group mt-3">
                <textarea class="form-control" name="message" rows="7" placeholder="Message" required=""></textarea>
              </div>
              <div class="my-3">
                <div class="loading">Loading</div>
                <div class="error-message"></div>
                <div class="sent-message">Your message has been sent. Thank you!</div>
              </div>
              <div class="text-center"><button type="submit">Envoyer Message</button></div>
            </form>
          </div>

        </div>

      </div>
    </section><!-- End Contact Section -->

  </main><!-- End #main -->

  <!-- ======= Footer ======= -->
  <footer id="footer">
    <div class="footer-top">
      <div class="container">
        <div class="row">

          <div class="col-lg-3 col-md-6">
            <div class="footer-info">
              <h3>MediConnect</h3>
              <p>
                122 Rue Paul Armangot <br>
                94400, Vitry-sur-Seine<br><br>
                <strong>Phone:</strong> +33 1 23 45 67 89<br>
                <strong>Email:</strong> thi-thu-hien.dinh@etu.u-pec.fr<br>
              </p>
              <div class="social-links mt-3">
                <a href="#" class="twitter"><i class="bx bxl-twitter"></i></a>
                <a href="#" class="facebook"><i class="bx bxl-facebook"></i></a>
                <a href="#" class="instagram"><i class="bx bxl-instagram"></i></a>
                <a href="#" class="google-plus"><i class="bx bxl-skype"></i></a>
                <a href="#" class="linkedin"><i class="bx bxl-linkedin"></i></a>
              </div>
            </div>
          </div>

          <div class="col-lg-2 col-md-6 footer-links">
            <h4>Liens utiles</h4>
            <ul>
              <li><i class="bx bx-chevron-right"></i> <a href="#hero">Accueil</a></li>
              <li><i class="bx bx-chevron-right"></i> <a href="#mesure">Mesure</a></li>
              <li><i class="bx bx-chevron-right"></i> <a href="#contact">Contact</a></li>
            </ul>
          </div>

          <div class="col-lg-3 col-md-6 footer-links">
            <h4>Nos Mesures</h4>
            <ul>
              <li><i class="bx bx-chevron-right"></i> <a href="#mesure">Température</a></li>
              <li><i class="bx bx-chevron-right"></i> <a href="#mesure">Humidité</a></li>
              <li><i class="bx bx-chevron-right"></i> <a href="#mesure">Présence</a></li>
              <li><i class="bx bx-chevron-right"></i> <a href="#mesure">Distance (par rapport au capteur / la porte) </a></li>
            </ul>
          </div>

          <div class="col-lg-4 col-md-6 footer-newsletter">
            <h4>Notre Newsletter</h4>
            <p>Soyez au cœur de l'innovation médicale. Abonnez-vous pour ne rien manquer !</p>
            <form action="" method="post">
              <input type="email" name="email"><input type="submit" value="S'abonner">
            </form>

          </div>

        </div>
      </div>
    </div>

    <div class="container">
      <div class="copyright">
        &copy; Copyright <strong><span>MediConnect</span></strong>. Tous droits réservés
      </div>
      <div class="credits">
      </div>
    </div>
  </footer><!-- End Footer -->

  <div id="preloader"></div>
  <a href="#" class="back-to-top d-flex align-items-center justify-content-center"><i class="bi bi-arrow-up-short"></i></a>

  <!-- Vendor JS Files -->
  <script src="assets/vendor/purecounter/purecounter_vanilla.js"></script>
  <script src="assets/vendor/aos/aos.js"></script>
  <script src="assets/vendor/bootstrap/js/bootstrap.bundle.min.js"></script>
  <script src="assets/vendor/glightbox/js/glightbox.min.js"></script>
  <script src="assets/vendor/swiper/swiper-bundle.min.js"></script>
  <script src="assets/vendor/php-email-form/validate.js"></script>

  <!-- Template Main JS File -->
  <script src="assets/js/main.js"></script>

</body>

</html>