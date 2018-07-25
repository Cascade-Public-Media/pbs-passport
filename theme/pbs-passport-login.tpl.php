<?php
/**
 * @file
 * Passport Login
 *
 * Available custom variables:
 * - $login_urls: An array of login URLs for PBS-supported services:
 *   - pbs
 *   - google
 *   - facebook
 *   - create_pbs
 * - $station: An array of station data.
 *
 * @see template_preprocess_pbs_passport_login()
 */
?>

<div class="pbs_passport-login">
  <span>Use one of the services below to sign in:</span>
  <ul class="pbs_passport-services-list">
    <li>
      <a href="<?php print $login_urls['pbs']; ?>" class="pbs_passport-login-link pbs_passport-login-link-pbs">
        <span class="pbs_passport-login-icon">
          <svg width="172" height="172" viewBox="0 0 172 172" xmlns="http://www.w3.org/2000/svg">
            <title>PBS</title>
            <g fill="none" fill-rule="evenodd">
              <path d="M172 86c0 47.496-38.504 86-86 86S0 133.496 0 86 38.504 0 86 0s86 38.504 86 86" fill="#000"></path>
              <path d="M86.46 79.033a8.524 8.524 0 1 1-.002-17.048 8.524 8.524 0 0 1 .002 17.048zm6.819-42.002H67.233c-21.367 0-38.855 15.064-38.855 37.192 0 18.607 11.01 32.038 28.01 34.577v26.231h35v-25h4.459c5.633-1 9.54-4.509 9.54-9.739v-14.26h9.46l-21.57-49z" fill="#fff"></path><path d="M122.423 37.03h-14.06l21.37 49h-9.345v12.76c0 7.819-4 11.155-14 11.018v25.223h14v-25h4.246c4.047 0 9.754-3.401 9.754-9.786V86.03h9.321l-21.286-49z" fill="#fff"></path>
            </g>
          </svg>
        </span>
        <span class="pbs_passport-login-text">Sign in with PBS Account</span>
      </a>
    </li>
    <li class="pbs_passport-login-separator"><span>or</span></li>
    <li>
      <a href="<?php print $login_urls['google']; ?>" class="pbs_passport-login-link pbs_passport-login-link-google">
        <span class="pbs_passport-login-icon">
          <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 195.38 199.31">
            <title>Google</title>
            <path d="M.26 94.67C1.12 43.33 48.32-1.63 99.66.08c24.6-1.14 47.72 9.56 66.56 24.6A354.76 354.76 0 0 1 141 50.85c-22.65-15.65-54.86-20.13-77.51-2-32.49 22.37-33.92 75.27-2.75 99.4 30.31 27.5 87.59 13.85 96-28.26-19-.29-38 0-57-.62 0-11.32-.1-22.65 0-34 31.74-.1 63.47-.14 95.26.1 1.9 26.64-1.62 55-18 77-24.79 34.88-74.56 45.06-113.38 30.12S-3 136.64.26 94.67z" id="Layer_1-2" data-name="Layer 1"></path>
          </svg>
        </span>
        <span class="pbs_passport-login-text">Sign in with Google</span>
      </a>
    </li>
    <li>
      <a href="<?php print $login_urls['facebook']; ?>" class="pbs_passport-login-link pbs_passport-login-link-facebook">
        <span class="pbs_passport-login-icon">
          <svg width="80" height="171" viewBox="0 0 80 171" xmlns="http://www.w3.org/2000/svg">
            <title>Facebook</title>
            <path d="M53.036 55.806V41.072c0-2.212.102-3.925.31-5.135.206-1.213.674-2.405 1.402-3.582.725-1.175 1.902-1.988 3.527-2.437 1.627-.451 3.79-.675 6.488-.675h14.733V-.225H55.942c-13.63 0-23.417 3.233-29.366 9.7-5.949 6.47-8.923 15.997-8.923 28.587v17.744H.012v29.469h17.64v85.5h35.384v-85.5h23.553l3.113-29.47H53.036z" fill="#222" fill-rule="evenodd"></path>
          </svg>
        </span>
        <span class="pbs_passport-login-text">Sign in with Facebook</span>
      </a>
    </li>
  </ul>
  <p>
    Don’t have a PBS Account?<br/>
    <a href="<?php print $login_urls['create_pbs']; ?>">Create one now</a>
  </p>
</div>
