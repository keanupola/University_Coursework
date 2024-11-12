document.addEventListener("DOMContentLoaded", function() {

    var regexPatterns = {
        namePattern: /^[a-zA-Z'-]{2,}$/,
        emailPattern: /^(([^<>()[\]\\.,;:\s@"]+(\.[^<>()[\]\\.,;:\s@"]+)*)|(".+"))@((\[[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\.[0-9]{1,3}\])|(([a-zA-Z\-0-9]+\.)+[a-zA-Z]{2,}))$/,
        phoneNumberPattern: /^\d{10}$/,
        usernameAndPasswordPattern: /^.{6,}$/,
        commentsPattern: /\S+/
    };

    function validateNames(elementId) {
        var el = document.getElementById(elementId);
        var formGroup = el.closest('.form-group');
        var helpBlock = formGroup.querySelector('.help-block');
        el.addEventListener('blur', function() {
            var value = el.value.trim();
            var isValid = regexPatterns.namePattern.test(value);
            formGroup.classList.remove('has-success', 'has-error');
            helpBlock.textContent = '';

            if (isValid) {
                formGroup.classList.add('has-success');
            } else {
                formGroup.classList.add('has-error');
                helpBlock.textContent = 'Name must contain at least 2 alphabet characters and may include hyphens and apostrophes.';
            }
        });
    }

    function validateEmail(elementId) {
        var el = document.getElementById(elementId);
        var formGroup = el.closest('.form-group');
        var helpBlock = formGroup.querySelector('.help-block');
        el.addEventListener('blur', function() {
            var value = el.value.trim();
            var isValid = regexPatterns.emailPattern.test(value);
            formGroup.classList.remove('has-success', 'has-error');
            helpBlock.textContent = '';

            if (isValid) {
                formGroup.classList.add('has-success');
            } else {
                formGroup.classList.add('has-error');
                helpBlock.textContent = 'Please enter a valid email address.';
            }
        });
    }

    function validatePhoneNumber(elementId) {
        var el = document.getElementById(elementId);
        var formGroup = el.closest('.form-group');
        var helpBlock = formGroup.querySelector('.help-block');
        el.addEventListener('blur', function() {
            var value = el.value.trim();
            var isValid = regexPatterns.phoneNumberPattern.test(value);
            formGroup.classList.remove('has-success', 'has-error');
            helpBlock.textContent = '';

            if (isValid) {
                formGroup.classList.add('has-success');
            } else {
                formGroup.classList.add('has-error');
                helpBlock.textContent = 'Phone number must be exactly 10 digits.';
            }
        });
    }

    function validateCredentials(elementId) {
        var el = document.getElementById(elementId);
        var formGroup = el.closest('.form-group');
        var helpBlock = formGroup.querySelector('.help-block');
        el.addEventListener('blur', function() {
            var value = el.value.trim();
            var isValid = regexPatterns.usernameAndPasswordPattern.test(value);
            formGroup.classList.remove('has-success', 'has-error');
            helpBlock.textContent = '';

            if (isValid) {
                formGroup.classList.add('has-success');
            } else {
                formGroup.classList.add('has-error');
                helpBlock.textContent = 'This field must be at least 6 characters long.';
            }
        });
    }

    function validateComments(elementId) {
        var el = document.getElementById(elementId);
        var formGroup = el.closest('.form-group');
        var helpBlock = formGroup.querySelector('.help-block');
        el.addEventListener('blur', function() {
            var value = el.value.trim();
            var isValid = regexPatterns.commentsPattern.test(value);
            formGroup.classList.remove('has-success', 'has-error');
            helpBlock.textContent = '';

            if (isValid) {
                formGroup.classList.add('has-success');
            } else {
                formGroup.classList.add('has-error');
                helpBlock.textContent = 'Comments cannot be empty.';
            }
        });
    }

    // Apply shared function for first name and last name
    validateNames('firstName');
    validateNames('lastName');

    // Apply email function
    validateEmail('email');

    // Apply phone number function
    validatePhoneNumber('phoneNumber');

    // Apply shared function for username and password
    validateCredentials('username');
    validateCredentials('password');

    // Apply comments function
    validateComments('comments');
});
